#include "docugen.hpp"

#include <omni/crypto/md5>
#include <omni/crypto/sha1>
#include <omni/crypto/sha256>

namespace OmniDocuGen
{
    namespace Types
    {
        class FileHash
        {
            public:
                std::string FileName;
                std::string NameOnly;
                std::string SHA256;
                std::string SHA1;
                std::string MD5;
                std::string LastDate;
                std::string FileSizeLong;
                std::string FileSizeShort;

                explicit FileHash(const std::string& fname)
                {
                    //FileInfo fi = new FileInfo(fname);
                    size_t len = (omni::io::file::exists(fname) ? omni::io::file::get_size(fname) : 0);
                    this->FileName = fname;
                    this->NameOnly = omni::io::path::get_name(fname);
                    this->SHA1 = FileHash::GenerateHash(fname, HashType::SHA1);
                    this->SHA256 = FileHash::GenerateHash(fname, HashType::SHA256);
                    this->MD5 = FileHash::GenerateHash(fname, HashType::MD5);
                    this->LastDate = Util::LastWriteTime(fname);
                    this->FileSizeShort = Util::DiskSpaceToString(len, 1, "");
                    this->FileSizeLong = Util::Format("{0} ({1} bytes)", this->FileSizeShort, omni::string::to_string(len));
                }

                /// Generates the HEX value of a SHA256 hash
                /// <param name="file">The file to hash</param>
                /// <returns></returns>
                static std::string GenerateHash(const std::string& file, const Types::HashType& ht)
                {
                    try {
                        // Generate hash's
                        if (omni::io::file::exists(file)) {
                            switch (ht) {
                                case Types::HashType::SHA256:
                                    return omni::crypto::sha256::compute_binary_file_hash(file);
                                case Types::HashType::SHA1:
                                    return omni::crypto::sha1::compute_binary_file_hash(file);
                                case Types::HashType::MD5:
                                    return omni::crypto::md5::compute_binary_file_hash(file);
                            }
                        }
                    } catch (const std::exception& ex) {
                        Program::AddError(ex, Util::Format("{0} hash failure for file {1}", ht, file));
                    }
                    return "Invalid";
                }
        };

        class xcodeprojfile
        {
            public:
                std::string src_ref;
                std::string file_ref;
                std::string nm_path;
                std::string name;
                std::string full_path;

                xcodeprojfile(const std::string& fpath, const std::string& sr, const std::string& fr)
                {
                    //B729DBC00000000000000000
                    this->full_path = fpath;
                    this->nm_path = omni::io::path::get_name(fpath);
                    this->name = omni::io::path::get_name_without_extension(fpath);
                    this->src_ref = xcodeprojfile::GetNextRef(sr);
                    this->file_ref = xcodeprojfile::GetNextRef(fr);
                }

                static std::string GetNextRef(const std::string& rf)
                {
                    std::string fp = rf.substr(0, rf.size() - 2);
                    std::string ep = omni::string::replace_all(rf, fp, "");
                    int v = omni::string::util::to_type<int>(ep, 16);
                    std::stringstream ss;
                    ss << std::hex << std::setfill('0') << std::setw(2);
                    ss << (v + 1);
                    ep = ss.str();
                    if (ep.size() < 2) { ep = "0" + ep; }
                    return fp + ep;
                }
        };
    }

    namespace DocuGen
    {
        /// Gets the download info
        std::string _GetDLInfo(std::string dlhtml, const Types::FileHash& f)
        {
            std::string nm = omni::string::to_upper(f.NameOnly);
            dlhtml = omni::string::replace(dlhtml, Util::Format("<!-- INSERT {0} SIZE -->", nm), f.FileSizeLong);
            dlhtml = omni::string::replace(dlhtml, Util::Format("<!-- INSERT {0} DATE -->", nm), f.LastDate);
            dlhtml = omni::string::replace(dlhtml, Util::Format("<!-- INSERT {0} SHA256 -->", nm), f.SHA256);
            dlhtml = omni::string::replace(dlhtml, Util::Format("<!-- INSERT {0} SHA1 -->", nm), f.SHA1);
            dlhtml = omni::string::replace(dlhtml, Util::Format("<!-- INSERT {0} MD5 -->", nm), f.MD5);
            return dlhtml;
        }
    }
}

using namespace OmniDocuGen;

struct DocuGenThreadParam
{
    mutable OmniDocuGen::CodeGen::ptr_t cgen;
    bool isSrc;
    omni::sync::basic_thread* m_t;

    DocuGenThreadParam() :
        cgen(), isSrc(false), m_t(OMNI_NULL_PTR)
    { }

    DocuGenThreadParam(std::string f, bool isrc) :
        cgen(new CodeGen(f)), isSrc(isrc), m_t(OMNI_NULL_PTR)
    {
        //this->cgen = new CodeGen(f);
    }

    DocuGenThreadParam(const DocuGenThreadParam& cp) :
        cgen(cp.cgen), isSrc(cp.isSrc), m_t(cp.m_t)
    {
    }

    ~DocuGenThreadParam()
    {
    }

    DocuGenThreadParam& operator=(const DocuGenThreadParam& cp)
    {
        this->cgen = cp.cgen;
        this->isSrc = cp.isSrc;
        return *this;
    }

    void Start()
    {
        if (this->cgen) {
            this->m_t = new omni::sync::basic_thread(
                omni::sync::thread_start::bind<DocuGenThreadParam, &DocuGenThreadParam::_GenerateMIThread>(*this)
            );
        } else {
            Program::AddError("cgen is NULL!!");
        }
    }

    void Wait()
    {
        if (this->m_t != OMNI_NULL_PTR) {
            this->m_t->join();
            delete this->m_t;
        }
    }

    void _GenerateMIThread()
    {
        if (this->cgen && !Program::StopReq && omni::io::file::exists(this->cgen->SourceFile)) {
            omni::stopwatch sw;
            OmniDocuGen::DocuGen::CodeGenList.push_back(this->cgen);
            if (Program::StopReq) { return; }
            sw.start();
            if (this->isSrc) {
                this->cgen->GenerateSourceTypeInfo();
            } else {
                this->cgen->GenerateTypeInfo();
            }
            sw.stop();
            if (Program::StopReq) { return; }
            up("Parsed in {0}ms", omni::string::to_string(sw.elapsed_ms()));
        }
    }
};

void OmniDocuGen::DocuGen::_GenerateCGHtmlSynFileThread(CodeGen::ptr_t& c)
{
    if (!OmniDocuGen::Program::StopReq) {
        std::string nm = c->Name();
        try {
            // generate the HTML syntax file no matter the type
            OmniDocuGen::DocuGen::GenerateHtmlSyntax(c);
        } catch (const std::exception& ex) {
            OmniDocuGen::Program::AddError(ex, Util::Format("Error generating HTML file for {0}:", nm));
        }
    }
}

void OmniDocuGen::DocuGen::_GenerateClassIndexHtml()
{
    // generate classes/index.html
    if (!OmniDocuGen::Program::StopReq) {
        OmniDocuGen::Program::SetGenerationProgress(Types::GenerationStatus::ClassIndexStart);
        OmniDocuGen::DocuGen::GenerateClassesIndexHtml(OmniDocuGen::DocuGen::Classes, OmniDocuGen::DocuGen::AllMti);
        OmniDocuGen::Program::SetGenerationProgress(Types::GenerationStatus::ClassIndexComplete);
    }
}

void OmniDocuGen::DocuGen::_GenerateHtmlClassHelpNR()
{
    OmniDocuGen::DocuGen::GenerateHtmlClassHelp(OmniDocuGen::DocuGen::Classes, DocuGen::AllMti, false);
}

void OmniDocuGen::DocuGen::_GenerateHtmlSyntaxFilesThread()
{
    size_t idx = 0;
    size_t sz = 0;
    OmniDocuGen::DocuGen::m_synLock.lock();
    idx = OmniDocuGen::DocuGen::m_synIdx++;
    sz = OmniDocuGen::DocuGen::m_synList.size();
    OmniDocuGen::DocuGen::m_synLock.unlock();
    while (idx < sz) {
        OmniDocuGen::DocuGen::_GenerateCGHtmlSynFileThread(OmniDocuGen::DocuGen::m_synList[idx]);
        OmniDocuGen::DocuGen::m_synLock.lock();
        idx = OmniDocuGen::DocuGen::m_synIdx++;
        OmniDocuGen::DocuGen::m_synLock.unlock();
        if (OmniDocuGen::Program::StopReq) { break; }
    }
}

void OmniDocuGen::DocuGen::_GenerateClassFilesThread()
{
    size_t idx = 0;
    size_t sz = 0;
    bool recurse = false;
    OmniDocuGen::DocuGen::m_classLock.lock();
    idx = OmniDocuGen::DocuGen::m_classIdx++;
    sz = OmniDocuGen::DocuGen::m_classList.size();
    recurse = OmniDocuGen::DocuGen::m_classRecurse;
    OmniDocuGen::DocuGen::m_classLock.unlock();
    while (idx < sz) {
        if (OmniDocuGen::Program::StopReq) { break; }
        OmniDocuGen::DocuGen::GenerateHtmlClassHelp(OmniDocuGen::DocuGen::Classes, OmniDocuGen::DocuGen::m_classList[idx], recurse);
        if (OmniDocuGen::Program::StopReq) { break; }
        OmniDocuGen::DocuGen::m_classLock.lock();
        idx = OmniDocuGen::DocuGen::m_classIdx++;
        OmniDocuGen::DocuGen::m_classLock.unlock();
    }
}

void OmniDocuGen::DocuGen::_GenerateMacroOptionThreadFunc(const MacroOp& m)
{
    std::string ofile = omni::io::path::combine(OmniDocuGen::DocuGen::Options, omni::string::to_lower(m.Name)) + std::string(".html");
    std::string html = m.ToHTML();
    Util::WriteFile(ofile, html);
    if (omni::io::file::exists(ofile)) {
        if (OmniDocuGen::DocuGen::DoHashZipFiles) {
            html = replace_dl_html(html);
            Util::WriteFile(omni::string::replace(ofile, OmniDocuGen::DocuGen::Root, OmniDocuGen::OutPaths::TempOut), html);
        }
        up(2, "MACRO HTML: {0} wrote {1}", m.Name, ofile);
    } else {
        up(2, "MACRO HTML: {0} failed to write {1}", m.Name, ofile);
    }
}

void OmniDocuGen::DocuGen::_GenerateMacroOptionsThread()
{
    size_t idx = 0;
    size_t sz = 0;
    OmniDocuGen::DocuGen::m_macroLock.lock();
    idx = OmniDocuGen::DocuGen::m_macIdx++;
    sz = OmniDocuGen::DocuGen::m_macroList.size();
    OmniDocuGen::DocuGen::m_macroLock.unlock();
    while (idx < sz) {
        OmniDocuGen::DocuGen::_GenerateMacroOptionThreadFunc(OmniDocuGen::DocuGen::m_macroList[idx]);
        OmniDocuGen::DocuGen::m_macroLock.lock();
        idx = OmniDocuGen::DocuGen::m_macIdx++;
        OmniDocuGen::DocuGen::m_macroLock.unlock();
        if (OmniDocuGen::Program::StopReq) { break; }
    }
}

std::string OmniDocuGen::DocuGen::_GenBuildFileFromSrcs(const List<std::string>& srcs, const std::string& srcdir, const std::string& slash, const std::string& fmt, bool isnlwin, bool use_nl, bool trim_end)
{
    std::string oslash = ((slash == "/") ? "\\" : "/");
    std::string tmp2 = fmt;
    std::string rep = "";
    if (use_nl) { tmp2 += (isnlwin ? "\r\n" : "\n"); }
    if (omni::string::contains(tmp2, "{0}")) {
        foreach_c (std::string, src, srcs) {
            if (OmniDocuGen::Program::StopReq) { return ""; }
            if (omni::string::to_lower(omni::io::path::get_extension(*src)) == ".cxx") { continue; }
            rep += omni::string::replace_all(tmp2, "{0}", omni::string::replace_all(*src, oslash, slash));
        }
    }
    if (omni::string::contains(tmp2, "{0.nm}")) {
        foreach_c (std::string, src, srcs) {
            if (OmniDocuGen::Program::StopReq) { return ""; }
            if (omni::string::to_lower(omni::io::path::get_extension(*src)) == ".cxx") { continue; }
            rep += omni::string::replace_all(tmp2, "{0.nm}", omni::io::path::get_name_without_extension(*src));
        }
    }
    if (omni::string::contains(tmp2, "{0.nm_path}")) {
        foreach_c (std::string, src, srcs) {
            if (OmniDocuGen::Program::StopReq) { return ""; }
            if (omni::string::to_lower(omni::io::path::get_extension(*src)) == ".cxx") { continue; }
            rep += omni::string::replace_all(tmp2, "{0.nm_path}", omni::string::replace_all(omni::string::replace_all(*src, srcdir, ""), oslash, slash));
        }
    }
    if (!rep.empty() && trim_end) {
        rep = omni::string::trim_end(rep);
        if (omni::string::ends_with(rep, OMNI_PATH_SEPARATOR)) {
            rep = omni::string::trim_end(omni::string::trim_end(rep, OMNI_PATH_SEPARATOR));
        }
    }
    return rep;
}

std::string OmniDocuGen::DocuGen::_GenBuildFileFromSrcs(const List<std::string>& srcs, const std::string& srcdir, const std::string& slash, const std::string& fmt)
{
    return DocuGen::_GenBuildFileFromSrcs(srcs, srcdir, slash, fmt, false, false, false);
}

void OmniDocuGen::DocuGen::_GenBuildFile(const List<std::string>& hdrs, const List<std::string>& srcs, const std::string& srcdir, const std::string& file, const std::string& odir)
{
    if (omni::io::file::exist(file)) {
        // Read file
        std::string all = omni::io::file::get_contents(file);
        std::string tmp = "", tmp2 = "", rep = "";
        bool isnlwin = ((all.find('\r') > 0) && (all.find('\n') > 0));
        bool isxcode = omni::string::contains(all, OmniDocuGen::Constants::Tags::XCODE_PARSE);
        bool ismake = omni::string::contains(all, OmniDocuGen::Constants::Tags::MAKE_FILE);
        if (!isxcode) {
            if (ismake) {
                //#region "<zeriph_inline_makefile_source>"
                tmp = Util::GetTag(all, OmniDocuGen::Constants::Tags::MAKE_FILE);
                if (!tmp.empty()) {
                    tmp2 = Util::GetTagData(tmp, OmniDocuGen::Constants::Tags::MAKE_FILE);
                    rep = DocuGen::_GenBuildFileFromSrcs(srcs, srcdir, "", tmp2, isnlwin, true, true);
                    rep = omni::string::replace_all(omni::string::replace_all(rep, "\\", ""), "\n", "\n\t");
                    all = omni::string::replace_all(all, tmp, rep);
                    tmp = tmp2 = rep = "";
                }
            } else {
                // parse as 'regular' build file
                //#region inline parsing

                /*
                    <zeriph_inline_source>src="${src} ${omni_src_dir}/{0.nm_path}"</zeriph_inline_source>
                    <zeriph_inline_source>    $$OMNI_SRC_DIR/{0.nm_path} \</zeriph_inline_source>
                    <zeriph_inline_header>    $$OMNI_SRC_DIR/{0.nm_path} \</zeriph_inline_header>
                    OBJ  = <zeriph_inline_source_nonl>obj/{0.nm}.o</zeriph_inline_source_nonl> $(RES)

                    {0} = full path (/sourc/omni/application.cpp or /sourc/omni/omni_impl/thread/sys_thread_impl.cxx) <- cxx's aren't allowed though
                    {0.nm} = name only (sys_thread_impl or application)
                    {0.nm_path} = name/path (minus the source directory), i.e. omni/thread.hpp in /source/omni/omni/thread.hpp
                */

                //#region "<zeriph_inline_source>"
                tmp = Util::GetTag(all, OmniDocuGen::Constants::Tags::IL_SRC);
                if (!tmp.empty()) {
                    tmp2 = Util::GetTagData(tmp, OmniDocuGen::Constants::Tags::IL_SRC);
                    rep = DocuGen::_GenBuildFileFromSrcs(srcs, srcdir, tmp2.substr(0, 1), tmp2.substr(1), isnlwin, true, true);
                    all = omni::string::replace_all(all, tmp, rep);
                    tmp = tmp2 = rep = "";
                }
                //#endregion
                //#region "<zeriph_inline_header>"
                tmp = Util::GetTag(all, OmniDocuGen::Constants::Tags::IL_HDR);
                if (!tmp.empty()) {
                    tmp2 = Util::GetTagData(tmp, OmniDocuGen::Constants::Tags::IL_HDR);
                    rep = DocuGen::_GenBuildFileFromSrcs(hdrs, srcdir, tmp2.substr(0, 1), tmp2.substr(1), isnlwin, true, true);
                    all = omni::string::replace_all(all, tmp, rep);
                    tmp = tmp2 = rep = "";
                }
                //#endregion
                //#region "<zeriph_inline_source_nonl>"
                tmp = Util::GetTag(all, OmniDocuGen::Constants::Tags::IL_SRC_NONL);
                if (!tmp.empty()) {
                    tmp2 = Util::GetTagData(tmp, OmniDocuGen::Constants::Tags::IL_SRC_NONL);
                    rep = DocuGen::_GenBuildFileFromSrcs(srcs, srcdir, tmp2.substr(0, 1), tmp2.substr(1));
                    all = omni::string::replace_all(all, tmp, rep);
                    tmp = tmp2 = rep = "";
                }
                
                //#region omni full section parsing

                /*
                    <--- start zeriph omni section --->
                    {x.int_inc}
                    <zeriph_source_format>
                    <Unit filename="{0}" />
                    </zeriph_source_format>
                    <zeriph_header_format>
                    <Unit filename="{0}" />
                    </zeriph_header_format>
                    <zeriph_slash>/</zeriph_slash>
                    <zeriph_path>/source/omni/</zeriph_path>
                    <zeriph_tabspace>		</zeriph_tabspace>
                    <zeriph_virt_folder></zeriph_virt_folder>
                    <zeriph_virt_folder_rec>false</zeriph_virt_folder_rec>
                    <--- end zeriph omni section --->
                */

                //#region "<--- start zeriph omni section --->"
                tmp = Util::GetTag(all, OmniDocuGen::Constants::Tags::OMNI_SECTION);
                if (!tmp.empty()) {
                    rep = "";
                    tmp2 = omni::string::trim(Util::GetTagData(tmp, OmniDocuGen::Constants::Tags::OMNI_SECTION));
                    std::string nl = (isnlwin ? Util::WinLe : Util::NixLe);
                    List<std::string> splits;
                    std::string src_fmt = Util::GetTagData(tmp2, "zeriph_source_format");
                    std::string hdr_fmt = Util::GetTagData(tmp2, "zeriph_header_format");
                    std::string slash = Util::GetTagData(tmp2, "zeriph_slash");
                    std::string oslash = ((slash == "/") ? "\\" : "/");
                    std::string sdir = Util::GetTagData(tmp2, "zeriph_path");
                    std::string tbspc = Util::GetTagData(tmp2, "zeriph_tabspace");
                    std::string vfldr = Util::GetTagData(tmp2, "zeriph_virt_folder");
                    std::string vfldr_rec_data = Util::GetTagData(tmp2, "zeriph_virt_folder_rec");
                    bool has_vfldr = !vfldr.empty();
                    bool vfldr_rec = (vfldr_rec_data == "true");
                    bool has_int_inc = omni::string::contains(src_fmt, "{x.int_inc}");
                    bool src_only = hdr_fmt.empty() || hdr_fmt == "SOURCE_ONLY";
                    if (has_vfldr && !vfldr_rec) {
                        rep += omni::string::replace_all(vfldr, "{0}", "omni");
                        rep += omni::string::replace_all(vfldr, "{0}", "omni/omni");
                        vfldr = "";
                        has_vfldr = false;
                    }
                    std::string tval = "", t2 = "", pth = "";
                    if (!has_int_inc) {
                        //#region no_int_inc
                        // no integer incremental values
                        foreach_c (std::string, src, srcs) {
                            if (OmniDocuGen::Program::StopReq) { return; }
                            if (omni::string::to_lower(omni::io::path::get_extension(*src)) == ".cxx") { continue; }
                            pth = omni::string::replace_all(omni::string::replace_all(*src, srcdir, ""), oslash, slash);
                            tmp2 = omni::string::replace_all(src_fmt, "{0}", (sdir + pth));
                            tmp2 = omni::string::replace_all(tmp2, "{0.nm}", omni::io::path::get_name_without_extension(pth));
                            tmp2 = omni::string::replace_all(tmp2, "{0.nm_path}", pth);
                            if (has_vfldr) { tval += tmp2; } else { rep += tmp2; }
                        }
                        if (!src_only) {
                            std::string tval2 = "";
                            foreach_c (std::string, src, hdrs) {
                                if (OmniDocuGen::Program::StopReq) { return; }
                                pth = omni::string::replace_all(omni::string::replace_all(*src, srcdir, ""), oslash, slash);
                                tmp2 = omni::string::replace_all(hdr_fmt, "{0}", (sdir + pth));
                                tmp2 = omni::string::replace_all(tmp2, "{0.nm}", omni::io::path::get_name_without_extension(pth));
                                tmp2 = omni::string::replace_all(tmp2, "{0.nm_path}", pth);
                                if (has_vfldr) { tval2 += tmp2; } else { rep += tmp2; }
                            }
                            if (has_vfldr) {
                                t2 = omni::string::replace_all(vfldr, "{0}", "omni/omni");
                                splits = Util::Split(tval2, nl);
                                tval2 = "";
                                for (int z = 0; z < splits.size(); z++) {
                                    tval2 += (tbspc + splits[z]);
                                    if ((z + 1) < splits.size()) { tval2 += nl[0]; }
                                }
                                tval += omni::string::replace_all(t2, "{1}", tval2);
                            }
                        }
                        if (has_vfldr) {
                            t2 = omni::string::replace_all(vfldr, "{0}", "omni");
                            splits = Util::Split(tval, nl);
                            tval = "";
                            for (int z = 0; z < splits.size(); z++) {
                                tval += (tbspc + splits[z]);
                                if ((z + 1) < splits.size()) { tval += nl[0]; }
                            }
                            rep += omni::string::replace_all(t2, "{1}", tval);
                        }
                        //#endregion
                    } else {
                        //#region int_inc
                        int i = 0;
                        for (; i < srcs.size(); i++) {
                            if (omni::string::to_lower(omni::io::path::get_extension(srcs[i])) == ".cxx") { continue; }
                            pth = omni::string::replace_all(omni::string::replace_all(srcs[i], srcdir, ""), oslash, slash);
                            tmp2 = omni::string::replace_all(src_fmt, "{x.int_inc}", omni::string::to_string(i));
                            tmp2 = omni::string::replace_all(tmp2, "{0}", (sdir + pth));
                            tmp2 = omni::string::replace_all(tmp2, "{0.nm}", omni::io::path::get_name_without_extension(pth));
                            tmp2 = omni::string::replace_all(tmp2, "{0.nm_path}", pth);
                            if (has_vfldr) { tval += tmp2; } else { rep += tmp2; }
                        }
                        if (!src_only) {
                            std::string tval2 = "";
                            int x = 0;
                            for (; x < hdrs.size(); x++, i++) {
                                pth = omni::string::replace_all(omni::string::replace_all(hdrs[x], srcdir, ""), oslash, slash);
                                tmp2 = omni::string::replace_all(hdr_fmt, "{x.int_inc}", omni::string::to_string(i));
                                tmp2 = omni::string::replace_all(tmp2, "{0}", (sdir + pth));
                                tmp2 = omni::string::replace_all(tmp2, "{0.nm}", omni::io::path::get_name_without_extension(pth));
                                tmp2 = omni::string::replace_all(tmp2, "{0.nm_path}", pth);
                                if (has_vfldr) { tval2 += tmp2; } else { rep += tmp2; }
                            }
                            if (has_vfldr) {
                                t2 = omni::string::replace_all(vfldr, "{0}", "omni/omni");
                                splits = Util::Split(tval2, nl);
                                tval2 = "";
                                for (int z = 0; z < splits.size(); z++) {
                                    tval2 += (tbspc + splits[z]);
                                    if ((z + 1) < splits.size()) { tval2 += nl[0]; }
                                }
                                tval += omni::string::replace_all(t2, "{1}", tval2);
                            }
                        }
                        if (has_vfldr) {
                            t2 = omni::string::replace_all(vfldr, "{0}", "omni");
                            splits = Util::Split(tval, nl);
                            tval = "";
                            for (int z = 0; z < splits.size(); z++) {
                                tval += (tbspc + splits[z]);
                                if ((z + 1) < splits.size()) { tval += nl[0]; }
                            }
                            rep += omni::string::replace_all(t2, "{1}", tval);
                        }
                    }
                    splits = Util::Split(rep, nl);
                    rep = "";
                    for (int z = 0; z < splits.size(); z++) {
                        rep += (tbspc + splits[z]);
                        if ((z + 1) < splits.size()) { rep += nl[0]; }
                    }
                    all = omni::string::replace_all(all, tmp, rep);
                }
            }
        } else {
            // xcode project files require some 'special' handling :/
            //#region xcode parsing

            /*
                <zeriph_xcode_source_ref>
                <zeriph_xcode_file_ref>
                <zeriph_xcode_fref_hex>
                <zeriph_xcode_sref_hex>
                <zeriph_xcode_parse>
                
                {0.src_ref}, {0.file_ref}, {0} = full path,
                {0.nm_path} = name/path (minus the source directory)
                */
            List<Types::xcodeprojfile> xps;
            std::string trep = "";
            foreach_c (std::string, src, srcs) {
                if (omni::string::to_lower(omni::io::path::get_extension(*src)) == ".cxx") { continue; }
                if (xps.size() == 0) {
                    xps.push_back(Types::xcodeprojfile(omni::string::replace_all(*src, srcdir, "/source/omni/"),
                                            "B729DBC00000000000000000",
                                            "B729DBD00000000000000000"));
                } else {
                    xps.push_back(Types::xcodeprojfile(omni::string::replace_all(*src, srcdir, "/source/omni/"),
                                            xps[xps.size() - 1].src_ref,
                                            xps[xps.size() - 1].file_ref));
                }
            }
            rep = "";
            all = Util::GetTagData(all, OmniDocuGen::Constants::Tags::XCODE_PARSE);

            //#region XCODE_SREF
            tmp = Util::GetTag(all, OmniDocuGen::Constants::Tags::XCODE_SREF);
            if (!tmp.empty()) {
                trep = "";
                tmp2 = Util::GetTagData(tmp, OmniDocuGen::Constants::Tags::XCODE_SREF);
                foreach (Types::xcodeprojfile, x, xps) {
                    rep += omni::string::replace_all(omni::string::replace_all(omni::string::replace_all(omni::string::replace_all(tmp2, "{0.src_ref}", x->src_ref), "{0.file_ref}", x->file_ref), "{0}", x->full_path), "{0.nm_path}", x->nm_path);
                }
                all = omni::string::replace_all(all, tmp, rep);
                tmp = tmp2 = rep = "";
            }
            //#region XCODE_FREF
            tmp = Util::GetTag(all, OmniDocuGen::Constants::Tags::XCODE_FREF);
            if (!tmp.empty()) {
                trep = "";
                tmp2 = Util::GetTagData(tmp, OmniDocuGen::Constants::Tags::XCODE_FREF);
                foreach (Types::xcodeprojfile, x, xps) {
                    rep += omni::string::replace_all(omni::string::replace_all(omni::string::replace_all(omni::string::replace_all(tmp2, "{0.src_ref}", x->src_ref), "{0.file_ref}", x->file_ref), "{0}", x->full_path), "{0.nm_path}", x->nm_path);
                }
                all = omni::string::replace_all(all, tmp, rep);
                tmp = tmp2 = rep = "";
            }
            //#region XCODE_FHEX
            tmp = Util::GetTag(all, OmniDocuGen::Constants::Tags::XCODE_FHEX);
            if (!tmp.empty()) {
                trep = "";
                tmp2 = Util::GetTagData(tmp, OmniDocuGen::Constants::Tags::XCODE_FHEX);
                foreach (Types::xcodeprojfile, x, xps) {
                    rep += omni::string::replace_all(omni::string::replace_all(omni::string::replace_all(omni::string::replace_all(tmp2, "{0.src_ref}", x->src_ref), "{0.file_ref}", x->file_ref), "{0}", x->full_path), "{0.nm_path}", x->nm_path);
                }
                all = omni::string::replace_all(all, tmp, rep);
                tmp = tmp2 = rep = "";
            }
            //#region XCODE_SHEX
            tmp = Util::GetTag(all, OmniDocuGen::Constants::Tags::XCODE_SHEX);
            if (!tmp.empty()) {
                trep = "";
                tmp2 = Util::GetTagData(tmp, OmniDocuGen::Constants::Tags::XCODE_SHEX);
                foreach (Types::xcodeprojfile, x, xps) {
                    rep += omni::string::replace_all(omni::string::replace_all(omni::string::replace_all(omni::string::replace_all(tmp2, "{0.src_ref}", x->src_ref), "{0.file_ref}", x->file_ref), "{0}", x->full_path), "{0.nm_path}", x->nm_path);
                }
                all = omni::string::replace_all(all, tmp, rep);
                tmp = tmp2 = rep = "";
            }

        }
        Util::WriteFile(omni::io::path::combine(odir, omni::io::path::get_name(file)), all);
    } else {
        up("Error with file '{0}': not found", file);
    }
}

void OmniDocuGen::DocuGen::_GenBuildExamples(const List<std::string>& hdrs, const List<std::string>& srcs, const std::string& srcdir, const std::string& bdir, const std::string& odir)
{
    if (!omni::io::directory::exists(odir)) { omni::io::directory::create(odir); }
    omni::seq::std_string_t vals;
    omni::io::directory::get_directories(bdir, vals);
    omni_foreach (std::string, d, vals) {
        if (OmniDocuGen::Program::StopReq) { return; }
        DocuGen::_GenBuildExamples(hdrs, srcs, srcdir, *d, omni::io::path::combine(odir, omni::io::path::get_name(*d)));
    }
    vals.clear();
    omni::io::directory::get_files(bdir, vals);
    omni_foreach (std::string, f, vals) {
        if (OmniDocuGen::Program::StopReq) { return; }
        DocuGen::_GenBuildFile(hdrs, srcs, srcdir, *f, odir);
    }
}

void OmniDocuGen::DocuGen::_GenBF(const std::string& t, const std::string& o, const List<std::string>& hdrs, const List<std::string>& srcs, const std::string& srcdir)
{
    Util::WriteRedirect(o, "index.html", 1);
    omni::seq::std_string_t dirs;
    omni::io::directory::get_directories(o, dirs);
    omni_foreach (std::string, dir, dirs) {
        std::string tsz = omni::io::path::combine(o, (omni::io::path::get_name(*dir) + ".zip"));
        Util::DeleteFile(tsz);
        Util::ZipDirectory(*dir, tsz);
        if (omni::io::file::exists(tsz)) {
            try {
                if (Program::Profile) {
                    up(1, "Profile mode enabled, skipping delete of {0}", *dir);
                } else {
                    omni::io::directory::remove(*dir, true);
                }
            } catch (const std::exception& e) {
                Program::AddError(e);
            }
        }
    }
}

void OmniDocuGen::DocuGen::_GenerateTempHelp(std::string thelp)
{
    if (!omni::string::ends_with(thelp, OMNI_PATH_SEPARATOR)) { thelp += OMNI_PATH_SEPARATOR; }
    std::string html;
    std::string idx = omni::io::path::combine(DocuGen::Root, "index.html");
    omni::seq::std_string_t files;
    omni::io::directory::get_files(DocuGen::Root, files);
    Util::CopyDirectory(DocuGen::Build, omni::string::replace(DocuGen::Build, DocuGen::Root, thelp), true);
    files.push_back(omni::io::path::combine(DocuGen::Docs, "index.html"));
    files.push_back(omni::io::path::combine(DocuGen::Build, "index.html"));
    files.push_back(omni::io::path::combine(DocuGen::Examples, "index.html"));
    files.push_back(omni::io::path::combine(DocuGen::Docs, "license.txt"));
    omni_foreach (std::string, file, files) {
        if (!omni::io::file::exists(*file)) { continue; }
        html = omni::io::file::get_contents(*file);
        if (*file == idx) {
            std::string edlt = "<\\!--end download table-->";
            size_t pos = html.find("<\\!--start download table-->");
            if (pos != std::string::npos) {
                size_t ep = html.find(edlt, pos);
                if (ep != std::string::npos) {
                    ep += edlt.size();
                    html.replace(pos, (ep-pos), "");
                }
            }
        }
        Util::WriteFile(omni::string::replace(*file, DocuGen::Root, thelp), html);
    }
    Util::CopyDirectory(omni::io::path::combine(DocuGen::Root, "content"), omni::io::path::combine(thelp, "content"), true, false);
}

void OmniDocuGen::DocuGen::_DoClassIndex(void_t parm)
{
    OMNI_UNUSED(parm);
    OmniDocuGen::DocuGen::_GenerateClassIndexHtml();
}

static void _DoMacroOptions(void_t parm)
{
    OMNI_UNUSED(parm);
    OmniDocuGen::DocuGen::GenerateMacroOptions();
}

void OmniDocuGen::DocuGen::_DoAPI(void_t parm)
{
    OMNI_UNUSED(parm);
    OmniDocuGen::DocuGen::GenerateAPIs();
}

void OmniDocuGen::DocuGen::_DoFilesView(void_t parm)
{
    OMNI_UNUSED(parm);
    OmniDocuGen::DocuGen::GenerateFilesViewHtml();
}

static void _DoExamples(void_t parm)
{
    OMNI_UNUSED(parm);
    OmniDocuGen::DocuGen::GenerateExamplesHtml();
}

static void _DoSyntax(void_t parm)
{
    OMNI_UNUSED(parm);
    OmniDocuGen::DocuGen::GenerateHtmlSyntaxFiles();
}

static void _DoClasses(void_t parm)
{
    OMNI_UNUSED(parm);
    OmniDocuGen::DocuGen::GenerateClassFiles();
}

static void _DoBuildFiles(void_t parm)
{
    OMNI_UNUSED(parm);
    if (OmniDocuGen::Program::StopReq) { return; }
    OmniDocuGen::DocuGen::GenerateBuildFiles();
}

static void _DoJs(void_t parm)
{
    OMNI_UNUSED(parm);
    if (OmniDocuGen::Program::StopReq) { return; }
    OmniDocuGen::DocuGen::GenerateJavaScriptSearchList();
}

static void _DoGenMacOptions(void_t parm)
{
    OMNI_UNUSED(parm);
    OmniDocuGen::DocuGen::_GenerateMacroOptionsThread();
}

static void _DoGenClassFiles(void_t parm)
{
    OMNI_UNUSED(parm);
    OmniDocuGen::DocuGen::_GenerateHtmlClassHelpNR();
}

static void _DoGenClassMemberFiles(void_t parm)
{
    OMNI_UNUSED(parm);
    OmniDocuGen::DocuGen::_GenerateClassFilesThread();
}

static void _DoGenHtmlSyntaxFiles(void_t parm)
{
    OMNI_UNUSED(parm);
    OmniDocuGen::DocuGen::_GenerateHtmlSyntaxFilesThread();
}

static void _DoWaitAllClassMemberFiles()
{
    size_t idx, sz;
    OmniDocuGen::DocuGen::m_classLock.lock();
    idx = OmniDocuGen::DocuGen::m_classIdx;
    sz = OmniDocuGen::DocuGen::m_classList.size();
    OmniDocuGen::DocuGen::m_classLock.unlock();
    while (idx < sz) {
        if (OmniDocuGen::Program::StopReq) { break; }
        OmniDocuGen::DocuGen::m_classLock.lock();
        idx = OmniDocuGen::DocuGen::m_classIdx;
        OmniDocuGen::DocuGen::m_classLock.unlock();
        omni::sync::sleep(50);
    }
}

static void _DoWaitAllHtmlFiles()
{
    size_t idx, sz;
    OmniDocuGen::DocuGen::m_synLock.lock();
    idx = OmniDocuGen::DocuGen::m_synIdx;
    sz = OmniDocuGen::DocuGen::m_synList.size();
    OmniDocuGen::DocuGen::m_synLock.unlock();
    while (idx < sz) {
        if (OmniDocuGen::Program::StopReq) { break; }
        OmniDocuGen::DocuGen::m_synLock.lock();
        idx = OmniDocuGen::DocuGen::m_synIdx;
        OmniDocuGen::DocuGen::m_synLock.unlock();
        omni::sync::sleep(50);
    }
}

static bool _CompareExampleDirectoryNames(const std::string& d1, const std::string& d2)
{
    size_t p1 = d1.find("_");
    size_t p2 = d2.find("_");
    std::string v1 = d1.substr(0, ((p1 == std::string::npos) ? (d1.size()-1) : p1));
    std::string v2 = d2.substr(0, ((p2 == std::string::npos) ? (d2.size()-1) : p2));
    if (omni::string::is_numeric(v1) && omni::string::is_numeric(v2)) {
        int i1 = omni::string::util::to_type<int>(v1);
        int i2 = omni::string::util::to_type<int>(v2);
        return i1 < i2;
    }
    return d1 < d2;
}

/// Creates and moves the zips
/// <param name="tpath">The temp path to store the zips</param>
/// <param name="srcdir">The 'src' dir to zip</param>
/// <param name="outdir">The 'wwwdocs' dir to zip</param>
/// <param name="fdir">The 'wwwdocs/files' dir to out to</param>
/// <param name="fsz">The 'files/src.zip' file</param>
/// <param name="fhz">The 'files/help.zip' file</param>
/// <param name="foz">The 'files/omni.zip' file</param>
void OmniDocuGen::DocuGen::_CreateAndMoveZips(const std::string& tpath, const std::string& srcdir, const std::string& thelp, const std::string& fsz, const std::string& fhz, const std::string& foz, const std::string& fbz, const std::string& fez, const std::string& frz)
{
    std::string odgzipdir = OmniDocuGen::OutPaths::ZipDir;
    if (!omni::io::directory::exists(odgzipdir)) {
        omni::io::directory::create(odgzipdir);
    }

    omni::stopwatch sw;
    std::string toz = omni::io::path::combine(tpath, "omni.zip");
    std::string tsz = omni::io::path::combine(odgzipdir, "src.zip");
    std::string boz = omni::io::path::combine(odgzipdir, "build.zip");
    std::string eoz = omni::io::path::combine(odgzipdir, "examples.zip");
    std::string thz = omni::io::path::combine(odgzipdir, "help.zip");
    std::string trz = omni::io::path::combine(odgzipdir, "raw_src.zip");

    up("Deleting/moving old zip files");
    Util::DeleteFile(fsz);
    Util::DeleteFile(foz);
    Util::DeleteFile(fhz);
    Util::DeleteFile(fbz);
    Util::DeleteFile(frz);
    Util::MoveFile(fez, eoz);

    up("Compressing {0} -> src.zip", srcdir);
    Util::DeleteFile(tsz);
    sw.start();
    Util::ZipDirectory(srcdir, tsz, true);
    up("Finished src.zip in {0}s", omni::string::to_string(sw.elapsed_s()));

    up("Compressing {0} -> raw_src.zip", Program::Settings.SourceDirectory);
    Util::DeleteFile(trz);
    sw.restart();
    Util::ZipDirectory(Program::Settings.SourceDirectory, trz, true);
    up("Finished raw_src.zip in {0}s", omni::string::to_string(sw.elapsed_s()));

    up("Compressing {0} -> help.zip", thelp);
    Util::DeleteFile(thz);
    sw.restart();
    Util::ZipDirectory(thelp, thz);
    up("Finished help.zip in {0}s", omni::string::to_string(sw.elapsed_s()));

    up("Compressing *.zip -> omni.zip");
    Util::DeleteFile(toz);
    sw.restart();
    Util::ZipDirectory(odgzipdir, toz);
    OmniDocuGen::Util::RemoveEntryFromZip(toz, "zips/omni.zip");
    up("Finished omni.zip in {0}s", omni::string::to_string(sw.elapsed_s()));

    up("Moving zips to html directory");
    Util::MoveFile(tsz, fsz);
    Util::MoveFile(thz, fhz);
    Util::MoveFile(toz, foz);
    Util::MoveFile(boz, fbz);
    Util::MoveFile(eoz, fez);
    Util::MoveFile(trz, frz);
    up("Done!");
}

/// Searchs the specified file for the 'start/end dl table' tags
/// and replaces with the hash table info
/// <param name="file">The file to search</param>
/// <param name="hsh">The hash</param>
void OmniDocuGen::DocuGen::_SetHashInFile(const std::string& file, const std::string& hsh)
{
    std::string t = omni::io::file::get_contents(file);
    std::string tmp = "<!--start download table-->";
    int tstrt = t.find(tmp) + tmp.size() + 1;
    if (tstrt >= 0) {
        int tend = t.find("<!--end download table-->");
        std::string html = "";
        if (tend > tstrt) {
            std::string otbl = t.substr(tstrt, (tend - tstrt));
            html = omni::string::replace_all(t, otbl, hsh);
        } else if (tend == tstrt) {
            html = t.insert(tend, hsh);
        }
        Util::WriteFile(file, html);
    }
}

void OmniDocuGen::DocuGen::_WriteIndexHtmlExampleCPP()
{
    // write the /index.html example
    std::string cpp = omni::io::path::combine(OmniDocuGen::Program::Settings.FrameworkExampleDirectory(), "index_html.cpp");
    if (omni::io::file::exists(cpp)) {
        std::string file = omni::io::path::combine(DocuGen::Root, "index.html");
        std::string t = omni::io::file::get_contents(file);
        std::string tmp = "<!--start index example-->";
        int tstrt = t.find(tmp) + tmp.size() + 1;
        if (tstrt >= 0) {
            int tend = t.find("<!--end index example-->");
            std::string html = "";
            std::string hsh =
                "<div class=\"sntx\"><input type=\"checkbox\" id=\"c0\" name=\"c0\" checked /><label for=\"c0\"> example</label><pre>" +
                OmniDocuGen::DocuGen::GenerateHtmlSyntaxHighlight(omni::io::file::get_contents(cpp), "", "", OmniDocuGen::DocuGen::AllMti, true) +
                "</pre></div>";
            if (tend > tstrt) {
                html = t.substr(0, tstrt) + hsh + t.substr(tend);
            } else if (tend == tstrt) {
                html = t.insert(tend, hsh);
            }

            if (Util::WriteFile(file, html)) {
                up("Wrote {0} to index.html example", cpp);
            } else {
                OmniDocuGen::Program::AddError("Could not write index.html example");
            }
        }
    }
}

/// Generates the hashs and puts the download table in omni/index.html and omni/download.html
void OmniDocuGen::DocuGen::GenerateHashFiles()
{
    omni::stopwatch sw;
    std::string fsz = omni::io::path::combine(DocuGen::Files, "src.zip");
    std::string fhz = omni::io::path::combine(DocuGen::Files, "help.zip");
    std::string foz = omni::io::path::combine(DocuGen::Files, "omni.zip");
    std::string fbz = omni::io::path::combine(DocuGen::Files, "build.zip");
    std::string fez = omni::io::path::combine(DocuGen::Files, "examples.zip");
    std::string frz = omni::io::path::combine(DocuGen::Files, "raw_src.zip");
    std::string thelp = omni::io::path::combine(Program::Settings.TempZipDirectory, "help");

    try {
        if (!omni::io::directory::exists(Program::Settings.TempZipDirectory)) {
            omni::io::directory::create(Program::Settings.TempZipDirectory);
        }
    } catch (const std::exception& ex) {
        Program::AddError(ex);
    }
    up("Generating local help docs");
    sw.start();
    // DocuGen::_GenerateTempHelp(thelp);
    if (!omni::string::ends_with(thelp, OMNI_PATH_SEPARATOR)) { thelp += OMNI_PATH_SEPARATOR; }
    Util::CopyDirectory(DocuGen::Root, thelp, true, true);
    std::string thelp_files = omni::io::path::combine(thelp, "files");
    if (OmniDocuGen::Program::Profile) {
        up(1, "Profile mode enabled, skipping delete dir ('{0}'..", thelp_files);
    } else {
        omni::io::directory::remove(thelp_files, true);
    }
    up("Help docs generated in {0}ms ({1}s)",
        omni::string::to_string(sw.elapsed_ms()),
        omni::string::to_string(omni::math::round(static_cast<double>(sw.elapsed_ms())/1000, 3))
    );

    up("Zipping docs");
    sw.restart();
    DocuGen::_CreateAndMoveZips(Program::Settings.TempZipDirectory, DocuGen::FilesSource, thelp, fsz, fhz, foz, fbz, fez, frz);
    up("Total zip time {0}ms ({1}s)",
        omni::string::to_string(sw.elapsed_ms()),
        omni::string::to_string(omni::math::round(static_cast<double>(sw.elapsed_ms())/1000, 3))
    );

    // set 'omni/index.html' download table
    up("Generating hashes");
    sw.restart();
    Types::FileHash s(fsz);
    Types::FileHash h(fhz);
    Types::FileHash o(foz);
    Types::FileHash b(fbz);
    Types::FileHash e(fez);
    Types::FileHash r(frz);
    if (OmniDocuGen::Program::StopReq) { return; }

    omni::seq::std_string_t oldzips = Util::GetFileList(Program::Settings.PrevZipDirectory, false);
    std::string oziphtml = "";
    up("Hashes generated in {0}ms ({1}s)",
        omni::string::to_string(sw.elapsed_ms()),
        omni::string::to_string(omni::math::round(static_cast<double>(sw.elapsed_ms())/1000, 3))
    );

    std::sort(oldzips.begin(), oldzips.end());
    std::reverse(oldzips.begin(), oldzips.end());

    sw.restart();
    std::string fzshrt = Util::Format(Constants::HtmlHashTable, s.FileSizeShort, h.FileSizeShort, o.FileSizeShort);
    DocuGen::_SetHashInFile(omni::io::path::combine(DocuGen::Root, "index.html"), fzshrt);

    if (OmniDocuGen::Program::StopReq) { return; }

    /* <!-- INSERT SRC.ZIP SIZE --> */
    std::string html = DocuGen::_GetDLInfo(Program::Settings.HtmlDownloadTemplate, s);
    /* <!-- INSERT HELP.ZIP SIZE --> */
    html = DocuGen::_GetDLInfo(html, h);
    /* <!-- INSERT EXAMPLES.ZIP SIZE --> */
    html = DocuGen::_GetDLInfo(html, e);
    /* <!-- INSERT BUILD.ZIP SIZE --> */
    html = DocuGen::_GetDLInfo(html, b);
    /* <!-- INSERT RAW_SRC.ZIP SIZE --> */
    html = DocuGen::_GetDLInfo(html, r);
    /* <!-- INSERT OMNI.ZIP SIZE --> */
    html = DocuGen::_GetDLInfo(html, o);
    /* <!-- INSERT OMNI VER --> */
    html = omni::string::replace(html, "<!-- INSERT OMNI VER -->", std::string(OMNI_FW_VER_STR));

    if (OmniDocuGen::Program::StopReq) { return; }

    for (int i = 0; i < oldzips.size(); ++i) {
        if (OmniDocuGen::Program::StopReq) { return; }
        oziphtml += Util::Format("<li><a href=\"files/prev/{0}\">{0}</a></li>", omni::io::path::get_name(oldzips[i]));
        if (i < (oldzips.size() - 1)) { oziphtml += "<li><div></div></li>"; }
    }
    if (oziphtml.empty()) { oziphtml = "None."; }
    /* <!-- INSERT PREV --> */
    html = omni::string::replace(html, "<!-- INSERT PREV -->", oziphtml);
    Util::WriteFile(omni::io::path::combine(DocuGen::Root, "download.html"), html);
    sw.stop();
    up("Hash tables generated in {0}ms ({1}s)",
        omni::string::to_string(sw.elapsed_ms()),
        omni::string::to_string(omni::math::round(static_cast<double>(sw.elapsed_ms())/1000, 3))
    );
}

/// Generates the IDE build files for Qt/VS/Eclipse/CodeBlocks
/// <param name="hdrs">The list headers to use</param>
/// <param name="srcs">The list of source to use</param>
/// <param name="bdir">The build example directory to scan</param>
/// <param name="outdir">The output directory to save the build files to</param>
void OmniDocuGen::DocuGen::GenerateBuildFiles()
{
    Program::SetGenerationProgress(Types::GenerationStatus::BuildStart);
    std::string bz = omni::io::path::combine(OmniDocuGen::OutPaths::ZipDir, "build.zip");
    List<std::string> now;// = { "nix", "osx", "win" };
    now.push_back("nix");
    now.push_back("osx");
    now.push_back("win");
    std::string bn = omni::io::path::combine(Program::Settings.BuildExDirectory(), now[0]);
    std::string on = omni::io::path::combine(DocuGen::Build, now[0]);
    std::string bo = omni::io::path::combine(Program::Settings.BuildExDirectory(), now[1]);
    std::string oo = omni::io::path::combine(DocuGen::Build, now[1]);
    std::string bw = omni::io::path::combine(Program::Settings.BuildExDirectory(), now[2]);
    std::string ow = omni::io::path::combine(DocuGen::Build, now[2]);
    Util::DeleteFile(bz);
    Util::CheckAndCreateDir(on);
    Util::CheckAndCreateDir(oo);
    Util::CheckAndCreateDir(ow);

    try {
        DocuGen::_GenBuildExamples(DocuGen::HeaderFiles, DocuGen::SourceFiles, Program::Settings.SourceDirectory, bn, on);
    } catch (const std::exception& ex) {
        Program::AddError(ex, "Here1");
    }
    
    try {
        DocuGen::_GenBuildExamples(DocuGen::HeaderFiles, DocuGen::SourceFiles, Program::Settings.SourceDirectory, bo, oo);
    } catch (const std::exception& ex) {
        Program::AddError(ex, "Here2");
    }
    
    try {
        DocuGen::_GenBuildExamples(DocuGen::HeaderFiles, DocuGen::SourceFiles, Program::Settings.SourceDirectory, bw, ow);
    } catch (const std::exception& ex) {
        Program::AddError(ex, "Here3");
    }
    
    up("Example files generated, zipping.");
    Util::ZipDirectory(DocuGen::Build, bz);
    Util::RemoveEntryFromZip(bz, "index.html");
    DocuGen::_GenBF(bn, on, DocuGen::HeaderFiles, DocuGen::SourceFiles, Program::Settings.SourceDirectory);
    DocuGen::_GenBF(bo, oo, DocuGen::HeaderFiles, DocuGen::SourceFiles, Program::Settings.SourceDirectory);
    DocuGen::_GenBF(bw, ow, DocuGen::HeaderFiles, DocuGen::SourceFiles, Program::Settings.SourceDirectory);
    Program::SetGenerationProgress(Types::GenerationStatus::BuildComplete);
}

void OmniDocuGen::DocuGen::GenerateHtmlSyntaxFiles(List<CodeGen::ptr_t>& files)
{
    OmniDocuGen::DocuGen::m_synList.clear();
    OmniDocuGen::DocuGen::m_synList.assign(files.begin(), files.end());
    if (OmniDocuGen::Program::SingleThreaded) {
        while (OmniDocuGen::DocuGen::m_synList.size() > 0) {
            CodeGen::ptr_t c = OmniDocuGen::DocuGen::m_synList[0];
            OmniDocuGen::DocuGen::m_synList.erase(OmniDocuGen::DocuGen::m_synList.begin());
            OmniDocuGen::DocuGen::_GenerateCGHtmlSynFileThread(c);
            if (OmniDocuGen::Program::StopReq) { break; }
        }
    } else {
        for (int32_t i = 0; i < OmniDocuGen::Program::MaxHtmlSyntaxThreads; ++i) {
            OmniDocuGen::Program::Tasks.queue(_DoGenHtmlSyntaxFiles);
        }
        _DoWaitAllHtmlFiles();
    }
    OmniDocuGen::DocuGen::m_synList.clear();
}

/// Generate the html syntax highlighted files
/// <param name="allmti"></param>
void OmniDocuGen::DocuGen::GenerateHtmlSyntaxFiles()
{
    OmniDocuGen::Program::SetGenerationProgress(Types::GenerationStatus::HtmlSyntaxStart);
    OmniDocuGen::DocuGen::GenerateHtmlSyntaxFiles(OmniDocuGen::DocuGen::CodeGenList);
    // generate omnilib
    CodeGen::ptr_t olib(new CodeGen(omni::io::path::combine(Program::Settings.SourceDirectory, "omnilib")));
    OmniDocuGen::DocuGen::GenerateHtmlSyntax(olib);
    Util::WriteRedirectDirectories(omni::io::path::combine(OmniDocuGen::DocuGen::HtmlSyntax, "omni"), "index.html", 1);
    OmniDocuGen::Program::SetGenerationProgress(Types::GenerationStatus::HtmlSyntaxComplete);
}

void OmniDocuGen::DocuGen::GenerateClassFiles(List<MemberTypeInformation::ptr_t>& members, bool recurse)
{
    OmniDocuGen::DocuGen::m_classList.clear();
    omni::sequence::add_range(OmniDocuGen::DocuGen::m_classList, members);
    if (OmniDocuGen::Program::SingleThreaded) {
        size_t sz = OmniDocuGen::DocuGen::m_classList.size();
        for (size_t idx = 0; idx < sz; ++idx) {
            if (OmniDocuGen::Program::StopReq) { return; }
            OmniDocuGen::DocuGen::GenerateHtmlClassHelp(OmniDocuGen::DocuGen::Classes, OmniDocuGen::DocuGen::m_classList[idx], recurse);
        }
    } else {
        OmniDocuGen::DocuGen::m_classRecurse = recurse;
        for (int32_t i = 0; i < OmniDocuGen::Program::MaxMtiThreads; ++i) {
            OmniDocuGen::Program::Tasks.queue(_DoGenClassMemberFiles);
        }
        _DoWaitAllClassMemberFiles();
    }
    OmniDocuGen::DocuGen::m_classList.clear();
}

/// Generates the class help documentation and the class index tree list
/// <param name="allmti"></param>
/// <param name="clsdir"></param>
void OmniDocuGen::DocuGen::GenerateClassFiles()
{
    // generate the class help (classes/omni_name.html) based on the parsed info, start 'omni.html'
    OmniDocuGen::Program::SetGenerationProgress(Types::GenerationStatus::ClassesStart);
    if (OmniDocuGen::Program::StopReq) { return; }
    if (OmniDocuGen::Program::SingleThreaded) {
        OmniDocuGen::DocuGen::_GenerateHtmlClassHelpNR();
    } else {
        OmniDocuGen::Program::Tasks.queue(_DoGenClassFiles);
    }
    OmniDocuGen::DocuGen::GenerateClassFiles(OmniDocuGen::DocuGen::AllMti->Members, true);
    OmniDocuGen::Program::SetGenerationProgress(Types::GenerationStatus::ClassesComplete);
}

void OmniDocuGen::DocuGen::GenerateExamplesZipFile()
{
    std::string exzip = omni::io::path::combine(OmniDocuGen::OutPaths::ZipDir, "examples.zip");
    Util::DeleteFile(exzip);
    if (Util::ZipDirectory(OmniDocuGen::Program::Settings.ExampleDirectory, exzip)) {
        std::string fez = omni::io::path::combine(OmniDocuGen::DocuGen::Files, "examples.zip");
        Util::RemoveEntryFromZip(exzip, std::string("build/"));
        Util::RemoveEntryFromZip(exzip, std::string("WORKING/"));
        Util::DeleteFile(fez);
        Util::MoveFile(exzip, fez);
        if (omni::io::file::exists(fez)) {
            up("Created {0}", fez);
        }
    } else {
        OmniDocuGen::Program::AddError("There was an error generating the examples.zip file");
    }
}

void OmniDocuGen::DocuGen::GenerateExampleIndexHtml(bool writeHtml)
{
    DocuGen::_WriteIndexHtmlExampleCPP();

    std::string exhtml = "The following are examples and use cases of the Omni library. "
        "The <a href=\"../../files/examples.zip\">full set of examples</a> can be downloaded from the "
        "<a href=\"../../download.html\">files</a> section.<br><br>If you're just starting with the library "
        "this list is ordered in such a way as to help familiarize you with the basic library structures, "
        "classes and options to get you building with Omni quicker.<br><br>";
    std::string fname = "";
    List<FrameworkExample> exs;
    omni::seq::std_string_t dirs;
    omni::io::directory::get_directories(OmniDocuGen::Program::Settings.FrameworkExampleDirectory(), dirs);
    std::sort(dirs.begin(), dirs.end(), _CompareExampleDirectoryNames);
    omni_foreach (std::string, dir, dirs) {
        if (OmniDocuGen::Program::StopReq) { return; }
        try {
            FrameworkExample ex(*dir);
            if (writeHtml) {
                fname = omni::io::path::combine(OmniDocuGen::DocuGen::Examples, (ex.HtmlFile));
                if (Util::WriteFile(fname, ex.ToHTML())) {
                    exhtml += ex.LiHtml();
                } else {
                    OmniDocuGen::Program::AddError(Util::Format("Could not write example file {0}", fname));
                }
            } else {
                exhtml += ex.LiHtml();
            }
        } catch (const std::exception& ex) {
            Program::AddError(ex, Util::Format("Framework example error for '{0}'", *dir));
        }
    }
    if (Util::WriteFile(OmniDocuGen::OutPaths::ExampleIndexHtml, Util::Format(OmniDocuGen::Program::Settings.HtmlExamples, "Examples", exhtml))) {
        if (OmniDocuGen::DocuGen::DoHashZipFiles) {
            exhtml = replace_dl_html(exhtml);
            Util::WriteFile(OmniDocuGen::OutPaths::TempExampleIndexHtml, exhtml);
        }
        up("Wrote examples file {0}", OmniDocuGen::OutPaths::ExampleIndexHtml);
    } else {
        OmniDocuGen::Program::AddError(Util::Format("Could not write examples file {0}", OmniDocuGen::OutPaths::ExampleIndexHtml));
    }
}

/// Zips the example directory
/// <param name="exdir"></param>
/// <param name="fdir"></param>
void OmniDocuGen::DocuGen::GenerateExamplesHtml()
{
    OmniDocuGen::Program::SetGenerationProgress(Types::GenerationStatus::ExStart);
    up("Generating HTML examples from {0}", OmniDocuGen::Program::Settings.FrameworkExampleDirectory());
    if (!omni::io::directory::exists(OmniDocuGen::Program::Settings.FrameworkExampleDirectory())) {
        OmniDocuGen::Program::AddError(Util::Format("{0} example directory not found", OmniDocuGen::Program::Settings.FrameworkExampleDirectory()));
        return;
    }
    DocuGen::GenerateExampleIndexHtml(true);
    OmniDocuGen::Program::SetGenerationProgress(Types::GenerationStatus::ExComplete);
}

/// Generate the sysapi directory
/// <param name="macdir">tools/docugen/sysapi/</param>
/// <param name="opdir">wwwdocs/docs/sysapi/</param>
void OmniDocuGen::DocuGen::GenerateAPIs()
{
    OmniDocuGen::Program::SetGenerationProgress(Types::GenerationStatus::ApiStart);
    up("Generating {0}", OmniDocuGen::OutPaths::ApiHtml);
    std::string chtml = OmniDocuGen::Program::Settings.HtmlSystemAPI;
    if (!chtml.empty()) {
        std::string win, apl, lnx, unx, psx, std, apih;
        win = apl = lnx = unx = psx = std = apih = "";
        std::sort(OmniDocuGen::DocuGen::SysAPIs.begin(), OmniDocuGen::DocuGen::SysAPIs.end());
        foreach (SysAPI, api, OmniDocuGen::DocuGen::SysAPIs) {
            if (OmniDocuGen::Program::StopReq) { return; }
            //if (api->IsNull()) { continue; }
            apih = api->ToHTML();
            switch (api->SysType) {
                case Types::SystemType::Windows: win += apih; break;
                case Types::SystemType::Apple: apl += apih; break;
                case Types::SystemType::Linux: lnx += apih; break;
                case Types::SystemType::Unix: unx += apih; break;
                case Types::SystemType::POSIX: psx += apih; break;
                case Types::SystemType::STD: std += apih; break;
            }
        }
        std::string html = omni::string::replace(chtml, "<!-- INSERT GENERATED WIN API CODE -->", win);
        html = omni::string::replace(html, "<!-- INSERT GENERATED APPLE API CODE -->", apl);
        html = omni::string::replace(html, "<!-- INSERT GENERATED LINUX API CODE -->", lnx);
        html = omni::string::replace(html, "<!-- INSERT GENERATED UNIX API CODE -->", unx);
        html = omni::string::replace(html, "<!-- INSERT GENERATED POSIX API CODE -->", psx);
        html = omni::string::replace(html, "<!-- INSERT GENERATED STD API CODE -->", std);
        if (Util::WriteFile(OmniDocuGen::OutPaths::ApiHtml, html)) {
            if (OmniDocuGen::DocuGen::DoHashZipFiles) {
                html = replace_dl_html(html);
                Util::WriteFile(OmniDocuGen::OutPaths::TempApiHtml, html);
            }
            up("Wrote system api file {0}", OmniDocuGen::OutPaths::ApiHtml);
        } else {
            OmniDocuGen::Program::AddError(Util::Format("Could not write system api file {0}", OmniDocuGen::OutPaths::ApiHtml));
        }
    } else {
        OmniDocuGen::Program::AddError("system_api template not found");
    }
    OmniDocuGen::Program::SetGenerationProgress(Types::GenerationStatus::ApiComplete);
}

void OmniDocuGen::DocuGen::GenerateMacroOptions(List<MacroOp> options)
{
    OmniDocuGen::DocuGen::m_macroList.clear();
    omni::sequence::add_range(OmniDocuGen::DocuGen::m_macroList, options);
    if (OmniDocuGen::Program::SingleThreaded) {
        while (OmniDocuGen::DocuGen::m_macroList.size() > 0) {
            MacroOp m(OmniDocuGen::DocuGen::m_macroList[0]);
            OmniDocuGen::DocuGen::m_macroList.erase(OmniDocuGen::DocuGen::m_macroList.begin());
            OmniDocuGen::DocuGen::_GenerateMacroOptionThreadFunc(m);
            if (OmniDocuGen::Program::StopReq) { return; }
        }
    } else {
        for (int32_t i = 0; i < OmniDocuGen::Program::MaxMacroTheads; ++i) {
            OmniDocuGen::Program::Tasks.queue(_DoGenMacOptions);
        }
    }
}

/// Generate the options directory
/// <param name="macdir">tools/docugen/options/</param>
/// <param name="opdir">wwwdocs/docs/options/</param>
void OmniDocuGen::DocuGen::GenerateMacroOptions()
{
    OmniDocuGen::Program::SetGenerationProgress(Types::GenerationStatus::MacroStart);
    std::string lis = "";
    std::string hlis = "";
    std::string flis = "";
    std::string clis = "";
    OmniDocuGen::DocuGen::GenerateMacroOptions(OmniDocuGen::DocuGen::Macros);
    foreach (MacroOp, m, OmniDocuGen::DocuGen::Macros) {
        if (OmniDocuGen::Program::StopReq) { return; }
        if (m->IsHelper || m->IsConstant || m->IsFWHelp) {
            if (m->IsConstant) {
                clis += m->LiHtmlString() + "\r\n";
            } else {
                if (m->IsFWHelp) {
                    flis += m->LiHtmlString() + "\r\n";
                } else {
                    hlis += m->LiHtmlString() + "\r\n";
                }
            }
        } else {
            lis += m->LiHtmlString() + "\r\n";
        }
    }
    std::string html = Util::Format(OmniDocuGen::Program::Settings.HtmlOptions, lis, hlis, flis, clis);
    if (Util::WriteFile(OmniDocuGen::OutPaths::OptionsIndexHtml, html)) {
        if (OmniDocuGen::DocuGen::DoHashZipFiles) {
            html = replace_dl_html(html);
            Util::WriteFile(OmniDocuGen::OutPaths::TempOptionsIndexHtml, html);
        }
        up("Wrote the macro/options file {0}", OmniDocuGen::OutPaths::OptionsIndexHtml);
    } else {
        OmniDocuGen::Program::AddError(Util::Format("Could not write the macro/options file {0}", OmniDocuGen::OutPaths::OptionsIndexHtml));
    }
    OmniDocuGen::Program::SetGenerationProgress(Types::GenerationStatus::MacroComplete);
}

void OmniDocuGen::DocuGen::GenerateJavaScriptSearchList()
{
    OmniDocuGen::Program::SetGenerationProgress(Types::GenerationStatus::JsStart);
    List<std::string> dirs;
    omni::seq::std_string_t jsfiles;
    std::string srcdocs = omni::io::path::combine(omni::io::path::combine(OmniDocuGen::Program::Settings.OutputDirectory, "files"), "src");
    std::string docs = omni::io::path::combine(OmniDocuGen::Program::Settings.OutputDirectory, "docs");
    // the order of added files will be the order of searching
    dirs.push_back(omni::io::path::combine(docs, "classes"));
    dirs.push_back(omni::io::path::combine(docs, "options"));
    dirs.push_back(omni::io::path::combine(docs, "examples"));
    dirs.push_back(srcdocs); // files/src/*
    dirs.push_back(OmniDocuGen::Program::Settings.OutputDirectory);
    dirs.push_back(docs);
    foreach (std::string, dir, dirs) {
        if (omni::io::directory::exists(*dir)) {
            if (*dir == srcdocs) {
                omni::sequence::add_range(jsfiles, Util::GetFileList(srcdocs, false));
            } else {
                omni::seq::std_string_t tfiles;
                omni::io::directory::get_files(*dir, tfiles);
                omni::sequence::add_range(jsfiles, tfiles);
            }
        }
    }
    jsfiles.push_back("files/index.html");
    jsfiles.push_back("docs/build/index.html");

    std::string jsfilename = omni::io::path::combine(omni::io::path::combine(OmniDocuGen::Program::Settings.OutputDirectory, "content"), "search_list.js");
    std::string html = "var searchList = [ ";
    for (int32_t i = 0; i < jsfiles.size()-1; ++i) {
        html += "\r\n\"" + omni::string::replace_all(omni::string::trim_front(omni::string::replace(jsfiles[i], OmniDocuGen::Program::Settings.OutputDirectory, ""), "/"), "\\", "/") + "\",";
    }
    html += "\r\n\"" + omni::string::replace_all(omni::string::trim_front(omni::string::replace(jsfiles[jsfiles.size() - 1], OmniDocuGen::Program::Settings.OutputDirectory, ""), "/"), "\\", "/") + "\"\r\n];";
    if (Util::WriteFile(jsfilename, html)) {
        up("Wrote javascript file {0}", jsfilename);
    } else {
        OmniDocuGen::Program::AddError(Util::Format("Could not write javascript file {0}", jsfilename));
    }
    OmniDocuGen::Program::SetGenerationProgress(Types::GenerationStatus::JSComplete);
}

void OmniDocuGen::DocuGen::CheckGenerateBuildJsHash()
{
    List<omni_task_t> tasks;
    // These must be done AFTER parsing (if parsing not done)
    if (OmniDocuGen::DocuGen::DoBuildFiles) { tasks.push_back(_DoBuildFiles); }
    if (OmniDocuGen::DocuGen::DoJs) { tasks.push_back(_DoJs); }
    if (OmniDocuGen::Program::SingleThreaded) {
        foreach (omni_task_t, task, tasks) {
            (*task)(void_t());
        }
    } else {
        foreach (omni_task_t, task, tasks) {
            OmniDocuGen::Program::Tasks.queue(*task);
        }
        OmniDocuGen::Program::Tasks.wait_active_queue();
    }
    if (OmniDocuGen::DocuGen::DoHashZipFiles) {
        OmniDocuGen::DocuGen::GenerateExamplesZipFile();
        DocuGen::GenerateHashFiles();
    }
}

void OmniDocuGen::DocuGen::GenerateAndBuild()
{
    OmniDocuGen::Program::SetGenerationProgress(Types::GenerationStatus::GenStart);
    List<omni_task_t> tasks;
    if (OmniDocuGen::DocuGen::ParseNeeded()) {
        // cleanup the docs/classes directory
        if ((OmniDocuGen::DocuGen::DoClassIndex || OmniDocuGen::DocuGen::DoClasses)) {
            OmniDocuGen::DocuGen::CheckClassDir();
        }
        
        // generate the class tree and classes/index.html
        if (OmniDocuGen::DocuGen::DoClassIndex) { tasks.push_back(_DoClassIndex); }
        // generate the options/index.html
        if (OmniDocuGen::DocuGen::DoMacroOptions) { tasks.push_back(_DoMacroOptions); }
        // generate the sysapi/index.html
        if (OmniDocuGen::DocuGen::DoAPI) { tasks.push_back(_DoAPI); }
        // generate the docs/htmlsrc/index.html...
        if (OmniDocuGen::DocuGen::DoFilesView) { tasks.push_back(_DoFilesView); }
        // generate the examples zip
        if (OmniDocuGen::DocuGen::DoExamples) { tasks.push_back(_DoExamples); }
        // generate the 'html highlighted' syntax files (docs/htmlsrc/...)
        if (OmniDocuGen::DocuGen::DoSyntax) { tasks.push_back(_DoSyntax); }
        // generate the class tree and classes/omni_name.html
        if (OmniDocuGen::DocuGen::DoClasses) { tasks.push_back(_DoClasses); }

        if (OmniDocuGen::Program::SingleThreaded) {
            foreach (omni_task_t, task, tasks) {
                (*task)(void_t());
            }
        } else {
            foreach (omni_task_t, task, tasks) {
                OmniDocuGen::Program::Tasks.queue(*task);
            }
            OmniDocuGen::Program::Tasks.wait_active_queue();
            // should be clear by this point, but just in case
            OmniDocuGen::Program::Tasks.clear_queue();
        }
        up("Parse build phase complete");
    }
    DocuGen::CheckGenerateBuildJsHash();
}

/// Scans the source directory and generates the member information
void OmniDocuGen::DocuGen::GenerateMemberInfo(bool isBuildToo)
{
    // NOTE: this doesn't necessarily need to use a thread pool since
    // it's the parser/generator and runs first before any other
    // threads (if parse is done) ... That being said, it is kind
    // of a messy function so could probably be cleaned up :/

    // scan and sort the source headers/files
    // parse code and generate type information from headers
    omni::stopwatch sw, gmi;
    List<DocuGenThreadParam> cgt;
    List<DocuGenThreadParam> parseables;
    
    gmi.start();
    up("Parsing {0} headers", omni::string::to_string(DocuGen::HeaderFiles.size()));
    sw.start();
    foreach (std::string, s, DocuGen::HeaderFiles) {
        if (OmniDocuGen::Program::StopReq) { return; }
        DocuGenThreadParam dp(*s, false);
        if (dp.cgen->HasParsableCode() || CodeGen::IsSpecialHeader(dp.cgen->SourceFile)) {
            parseables.push_back(dp);
            DocuGen::Parsables.push_back(dp.cgen);
        } else {
            if (Program::SingleThreaded) {
                dp._GenerateMIThread();
            } else {
                cgt.push_back(dp);
                cgt[cgt.size()-1].Start();
            }
        }
    }
    if (!Program::SingleThreaded) {
        up(1, "Waiting for initial threads to complete.");
        foreach (DocuGenThreadParam, val, cgt) {
            val->Wait();
        }
        cgt.clear();
    }

    if (Program::SingleThreaded) {
        for (int32_t i = 0; i < parseables.size(); ++i) {
            if (OmniDocuGen::Program::StopReq) { return; }
            if (omni::string::contains(parseables[i].cgen->SourceFile, "delegate" OMNI_PATH_SEPARATOR)) {
                if (OmniDocuGen::Program::StopReq) { return; }
                parseables[i]._GenerateMIThread();
                parseables.erase(parseables.begin()+i);
                --i;
            }
        }
        cgt.clear();
        foreach (DocuGenThreadParam, val, parseables) {
            if (OmniDocuGen::Program::StopReq) { return; }
            val->_GenerateMIThread();
        }
    } else {
        for (int32_t i = 0; i < parseables.size(); ++i) {
            if (OmniDocuGen::Program::StopReq) { return; }
            if (omni::string::contains(parseables[i].cgen->SourceFile, "delegate" OMNI_PATH_SEPARATOR)) {
                if (OmniDocuGen::Program::StopReq) { return; }
                cgt.push_back(parseables[i]);
                cgt[cgt.size()-1].Start();
                parseables.erase(parseables.begin()+i);
                --i;
            }
        }
        foreach (DocuGenThreadParam, vals, cgt) {
            vals->Wait();
        }
        cgt.clear();

        foreach (DocuGenThreadParam, val, parseables) {
            if (OmniDocuGen::Program::StopReq) { return; }
            val->Start();
        }
        foreach (DocuGenThreadParam, vals, parseables) {
            vals->Wait();
        }
    }
    parseables.clear();
    sw.stop();
    up("Headers parsed in {0}ms", omni::string::to_string(sw.elapsed_ms()));

    if (OmniDocuGen::Program::StopReq) { return; }
    up("Creating tree node structure of member information");
    sw.reset(); sw.start();
    DocuGen::AllMti = MemberTypeInformation::GetOmni(true);
    DocuGen::MtiTree.SetRoot(DocuGen::AllMti);
    foreach (CodeGen::ptr_t, c, DocuGen::Parsables) {
        if (OmniDocuGen::Program::StopReq) { return; }
        if (!(*c)->MemberInformation) { continue; }
        DocuGen::AllMti->AddVerify((*c)->MemberInformation);
        Types::TreeNode n((*c)->MemberInformation);
        foreach (MemberTypeInformation::ptr_t, ti, (*c)->MemberInformation->Members) {
            if (OmniDocuGen::Program::StopReq) { return; }
            DocuGen::AddTree(*ti, n);
        }
        if (!omni::string::contains(n.Text, ".hpp") && !omni::string::contains(n.Text, ".cpp") && !omni::string::contains(n.Text, ".hxx")) {
            Types::TreeNode::AddNodes(n, DocuGen::MtiTree);
        }
    }
    sw.stop();
    up("Initial tree time: {0}ms", omni::string::to_string(sw.elapsed_ms()));
    if (OmniDocuGen::Program::StopReq) { return; }
    up("Parsing {0} source implementations", omni::string::to_string(DocuGen::SourceFiles.size()));
    sw.reset(); sw.start();
    if (Program::SingleThreaded) {
        foreach (std::string, s, DocuGen::SourceFiles) {
            if (OmniDocuGen::Program::StopReq) { return; }
            (DocuGenThreadParam(*s, true))._GenerateMIThread();
        }
    } else {
        foreach (std::string, s, DocuGen::SourceFiles) {
            if (OmniDocuGen::Program::StopReq) { break; }
            cgt.push_back(DocuGenThreadParam(*s, true));
            cgt[cgt.size()-1].Start();
        }
        foreach (DocuGenThreadParam, vals, cgt) {
            vals->Wait();
        }
        cgt.clear();
    }
    sw.stop();
    up("Source files parsed in {0}ms", omni::string::to_string(sw.elapsed_ms()));
    up("Total parse time {0}ms", omni::string::to_string(gmi.elapsed_ms()));
}

void OmniDocuGen::DocuGen::StartBuild()
{
    omni::stopwatch bsw;
    try {
        bsw.start();
        OmniDocuGen::DocuGen::GenerateAndBuild();
        bsw.stop();
        up("Build generation {0}: {1}ms ({2}s)",
            (OmniDocuGen::Program::StopReq ? "stop requested" : "thread complete"),
            omni::string::to_string(bsw.elapsed_ms()),
            omni::string::to_string(omni::math::round((static_cast<double>(bsw.elapsed_ms()) / 1000), 3))
        );
    } catch (const std::exception& ex) {
        OmniDocuGen::Program::AddError(ex, "Error in generator thread");
    }
}
