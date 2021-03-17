#include "docugen.hpp"

using namespace OmniDocuGen;

static std::string replace_nums(std::string code)
{
    const char* nums = "0123456789";
    std::string rbeg = "<font class=\"syn_num\">";
    std::string rend = "</font>";
    size_t rsize = rbeg.size() + rend.size();
    std::string line, tmp;
    char bef, aft;
    code = omni::string::replace_all(code, "&#39;\\<font class=\"syn_num\">0</font>&#39;", "&#39;\\0&#39;");
    code = omni::string::replace_all(code, "&#39;", "'");
    size_t npos = code.find_first_of(nums);
    size_t epos, len, nlpos, elpos, np, ep;
    while (npos != std::string::npos) {
        if (OmniDocuGen::Program::StopReq) { break; }
        epos = code.find_first_not_of(nums, npos);
        if (epos == std::string::npos) { epos = code.size(); }
        len = epos - npos;
        aft = ((npos+1 < code.size()) ? code[npos+1] : code[npos]);
        bef = ((npos-1 >= 0) ? code[npos-1] : code[npos]);
        if (omni::char_util::is_alpha(bef) || bef == '_' || bef == '/' || bef == '\\' || bef == '\'' || aft == '\'' || aft == '_') {
            // check if it's a \', _, backslash or alpha
            npos = code.find_first_of(nums, epos);
            continue;
        }

        nlpos = code.rfind("\n", npos);
        if (nlpos == std::string::npos) { nlpos = 0; }
        elpos = code.find("\n", npos);
        if (elpos == std::string::npos) { elpos = code.size(); }
        
        line = code.substr(nlpos, elpos-nlpos);
        if (omni::string::contains(line, "&quot;")) {
            /*
                423 shouldn't be (in ""), 452112.419 should be .. etc.
                std::cout << "this 423 shouldn't be " << 452112.419 << " that should be, 44.12 .. no" << 412 << " yes" << std::endl;
            */
            typedef std::map<size_t, size_t> idx_map;
            idx_map idxs = Util::IndexOfCompliments(line, "&quot;", false);
            idx_map numx = Util::IndexOfCompliments(line, nums);
            List<idx_map::iterator> rems;
            size_t snx, enx, six, eix;
            std_foreach(idx_map, nx, numx) {
                if (OmniDocuGen::Program::StopReq) { return ""; }
                snx = nx->first;
                enx = nx->second;
                std_foreach(idx_map, ix, idxs) {
                    if (OmniDocuGen::Program::StopReq) { return ""; }
                    six = ix->first;
                    eix = ix->second;
                    if (((snx > six) && (snx < eix)) && ((enx > six) && (enx < eix))) {
                        // nx is within "", remove these indexs
                        rems.push_back(nx);
                        break;
                    }
                }
            }
            foreach (idx_map::iterator, rm, rems) {
                if (OmniDocuGen::Program::StopReq) { return ""; }
                numx.erase(*rm);
            }

            eix = 0;
            std_foreach(idx_map, nx, numx) {
                if (OmniDocuGen::Program::StopReq) { return ""; }
                snx = nx->first + nlpos + eix;
                enx = nx->second + nlpos + eix;
                len = enx - snx;
                line = code.substr(snx, len);
                tmp = rbeg + line + rend; //"<font class=\"syn_num\">$1</font>";
                // (size_t pos,  size_t len,  const string& str)
                code.replace(snx, len, tmp);
                eix += rsize;
                elpos += rsize;
            }

            npos = code.find_first_of(nums, elpos);
        } else {
            line = code.substr(npos, len);
            tmp = rbeg + line + rend; //"<font class=\"syn_num\">$1</font>";
            // (size_t pos,  size_t len,  const string& str)
            code.replace(npos, len, tmp);
            npos = code.find_first_of(nums, epos+rsize);
        }
    }
    return omni::string::replace_all(code, "'", "&#39;");
}

static std::string replace_chars(std::string code)
{
    typedef std::map<size_t, size_t> idx_map;
    std::string rbeg = "<font class=\"syn_chr\">";
    std::string rend = "</font>";
    std::string tmp, line;
    size_t rsize = rbeg.size() + rend.size();
    size_t nsz = 0;
    size_t s, e, l;
    code = omni::string::replace_all(code, "&#39;", "'");
    List<int32_t> qidx = Util::IndexesOf(code, "'");
    idx_map qts = Util::IndexOfCompliments(code, "&quot;", false);
    for (size_t i = 0; i < qidx.size(); ++i) {
        if (OmniDocuGen::Program::StopReq) { return ""; }
        s = code.rfind("/*", qidx[i]);
        if (s != std::string::npos) {
            // A /* C99 comment */ was found, so look for the
            // begining and end of the comment and see if the
            // single quote ['] is in there
            e = code.find("*/", s);
            if (e == std::string::npos) { e = code.size(); }
            if ((s < qidx[i]) && (e > qidx[i])) {
                //it's in a /* C99 comment */, so remove it
                qidx.erase(qidx.begin() + i);
                --i;
                continue;
            }
        }
        // now look for it in a single line [//] comment
        s = code.rfind("//", qidx[i]);
        if (s != std::string::npos) {
            // A [//] single line comment was found, so look for the
            // end of the line single quote ['] is in there
            e = code.find("\n", s);
            if (e == std::string::npos) { e = code.size(); }
            if ((s < qidx[i]) && (e > qidx[i])) {
                // it's in a single line comment, so remove it
                qidx.erase(qidx.begin() + i);
                --i;
                continue;
            }
        }
        // now look for it in between double quotes (i.e. strings), ["here's an example"]
        std_foreach(idx_map, ix, qts) {
            if (OmniDocuGen::Program::StopReq) { return ""; }
            // if the single quote ['] is between double quotes ["], it's likely
            // in a string of text, so remove it from our index
            s = ix->first;
            e = ix->second;
            if ((s < qidx[i]) && (e > qidx[i])) {
                qidx.erase(qidx.begin() + i);
                --i;
                // break out of this inner loop
                break;
            }
        }
    }
    foreach (int32_t, idx, qidx) {
        if (OmniDocuGen::Program::StopReq) { return ""; }
        s = (*idx) + nsz;
        if (++idx != qidx.end()) {
            e = (*idx) + nsz + 1;
            if (e > code.size()) {
                e = code.size();
            }
        } else {
            e = code.size();
        }
        l = (e - s);
        // examples of valid 'char's': 'A', 'a', '.', '1', '\\', '\n', ''
        line = code.substr(s, l);
        switch (l) {
            case 2: case 3: case 4: break;
            default:
                // it's an invalid pairing, decrement and try again
                --idx;
                continue;
        }
        tmp = rbeg + line + rend; //"<font class=\"syn_chr\">$1</font>";
        code.replace(s, l, tmp);
        nsz += rsize;
    }
    return omni::string::replace_all(code, "'", "&#39;");
}

static std::string InternalGenerateHtmlSyntaxHighlight(const std::string& code, const std::string& inchref, const std::string& dochref, MemberTypeInformation::ptr_t& allmti, bool docmntdiv, const std::string& adnlinc)
{
    std::string sntx = omni::string::trim_end(omni::string::replace_all(omni::string::replace_all(code, "\r", ""), "\n", "\r\n"));
    sntx = Util::ToHTML(sntx);
    sntx = Util::TabToWhitespaceHTML(sntx);
    /*
        // do instructions/types/num/char/op first
        // then link the headers/api/syscalls/member info
        // then do preproc
        // then string
        // then comments
        // this order ensures any nested <font> types are removed where they don't need to be
    */

    // keywords, numbers, chars
    sntx = DocuGen::ReplaceKeywords(sntx, omni::string::contains(sntx, "&#39;"), omni::string::contains(code, "\\0"));
    // <omni/*.hpp> -> <*.hpp.html>
    sntx = DocuGen::ReplaceIncludes(sntx, (inchref + adnlinc));
    // Link any OMNI_MACRO and SystemAPI found to their web counter parts
    sntx = DocuGen::ReplaceMacroInfo(sntx, (dochref + "options/"), false);
    sntx = DocuGen::ReplaceSysApiInfo(sntx, false);
    // Link any omni::xx members found to their web counter parts
    if (allmti) {
        foreach (MemberTypeInformation::ptr_t, mti, allmti->Members) {
            if (OmniDocuGen::Program::StopReq) { return ""; }
            sntx = DocuGen::ReplaceMemberInfo(*mti, sntx, (dochref + "classes/"), false);
        }
    }

    // preprocessor
    sntx = DocuGen::_ColorizePreproc(sntx);
    // std::string text
    sntx = DocuGen::_ColorizeStrings(sntx);
    // comments
    sntx = DocuGen::_ColorizeComments(sntx, docmntdiv);

    return sntx;
}

// -- html gen --

bool OmniDocuGen::DocuGen::_CompareFileNames(const std::string& fname1, const std::string& fname2)
{
    if (omni::string::contains(fname1, "delegate") &&
        omni::string::contains(fname2, "delegate"))
    {
        std::string v1 = omni::io::path::get_name_without_extension(fname1);
        std::string v2 = omni::io::path::get_name_without_extension(fname2);
        if (omni::string::is_numeric(v1) && omni::string::is_numeric(v2)) {
            int i1 = omni::string::util::to_type<int>(v1);
            int i2 = omni::string::util::to_type<int>(v2);
            return i1 < i2;
        }
    }
    return fname1 < fname2;
}

std::string OmniDocuGen::DocuGen::_GetFileViewTplate(const std::string& fname, const std::string& srcdir, bool verbose, bool includeNonHpp, bool isPlainText)
{
    // <li class="hpp" title="file: thread.hpp"><div>3.30 KB</div><div class="dt">3/10/2014 07:07:07 (-07 UTC)</div><a href="html/thread.hpp.html">thread.hpp</a></li>
    // {0} = name (blah.hpp)
    // {1} = type (cpp, cxx, hpp)
    // {2} = size (3.02 kb)
    // {3} = date (3/10/2014 07:07:07 (-07 UTC))
    // {4} = html_syntax_path (html/omni_impl/thread/sys_thread_impl.cxx.html)
    std::string exten = omni::io::path::get_extension(fname);
    bool exte = exten.empty();
    // return empty std::string if extension is empty and we only want .hpp/.cxx/etc. files
    if (!omni::string::ends_with(fname, "omnilib") && exte && !includeNonHpp) { return ""; }
    std::string type = (exte ? "hpp" : exten.substr(1));
    std::string nm = omni::io::path::get_name(fname);
    std::string hp = omni::string::replace_all(omni::string::replace(fname, srcdir, ""), "\\", "/");
    if (!isPlainText) { hp += ".html"; }
    if (!verbose) {
        return
            (isPlainText ?
            Util::Format("<li title=\"file: {0}\"><a href=\"src/{1}\">{0}</a></li>\r\n", nm, hp) :
            Util::Format("<li class=\"{1}\" title=\"file: {0}\"><a href=\"{2}\">{0}</a></li>\r\n", nm, type, hp));
    }
    std::string sz = Util::DiskSpaceToString(omni::io::file::get_size(fname), 2, "KB");
    std::string dt = Util::LastWriteTime(fname);
    return
        (isPlainText ?
        Util::Format("<li title=\"file: {0}\"><a href=\"src/{3}\">{0}</a> - {1} - {2}</li>\r\n", nm, sz, dt, hp) :
        Util::Format("<li class=\"{1}\" title=\"file: {0}\"><div>{2}</div><div class=\"dt\">{3}</div><a href=\"{4}\">{0}</a></li>\r\n", nm, type, sz, dt, hp)
        );
}

std::string OmniDocuGen::DocuGen::_GetFolderViewTplate(const std::string& dir, const std::string& srcdir, bool verbose, bool isPlainText)
{
    std::string r = Util::Format((isPlainText ? Constants::ViewFolderPlainTemplate : Constants::ViewFolderTemplate),
                                    omni::io::path::get_name(dir));
    std::string extol = omni::string::to_lower(Program::Settings.Excluded);
    omni::seq::std_string_t dirs;
    omni::io::directory::get_directories(dir, dirs);
    std::sort(dirs.begin(), dirs.end());
    foreach_t (omni::seq::std_string_t, subd, dirs) {
        if (OmniDocuGen::Program::StopReq) { return ""; }
        if (omni::string::contains(extol, omni::string::to_lower(*subd))) { continue; }
        r += DocuGen::_GetFolderViewTplate(*subd, srcdir, verbose, isPlainText);
    }
    omni::seq::std_string_t files;
    omni::io::directory::get_files(dir, files);
    std::sort(files.begin(), files.end(), DocuGen::_CompareFileNames);
    foreach_t (omni::seq::std_string_t, fl, files) {
        if (OmniDocuGen::Program::StopReq) { return ""; }
        if (omni::string::contains(extol, omni::string::to_lower(*fl))) { continue; }
        if (omni::io::path::get_extension(*fl).empty()) { continue; }
        r += DocuGen::_GetFileViewTplate(*fl, srcdir, verbose, false, isPlainText);
    }
    return
        (isPlainText ? (r + "</ul></li>") :
                        (r + "</ol></li>"));
}

std::string OmniDocuGen::DocuGen::_GenerateHtmlSyntaxFromTemplate(const std::string& name, const std::string& title, std::string sntx)
{
    sntx = omni::string::trim_end(sntx);
    List<std::string> splits = Util::SplitAtEndings(sntx);
    int32_t cmnti = 0, maxcmnt = 0;
    int32_t linecnt = splits.size();
    int32_t clen = (omni::string::to_string(linecnt)).size();
    std::string htfmt = "{0}:<br><div id=\"cmntl{1}\" name=\"cmntl{1}\">";
    std::string cfmt = "<img src=\"../../content/tree/min.gif\" alt=\"Min/Max\" id=\"cmnti{0}\" name=\"cmnti{0}\" onclick=\"collapse('{0}', '../../');\" /><br><div id=\"cmnts{0}\" name=\"cmnts{0}\">";
    std::string lvl = "";
    std::string htmllines = "";
    std::string collapse = "";
    std::string tmp = title;
    std::string cmstr = "";
    int32_t cmsz = std::string("id=\"cmnt").size();
    while (omni::string::contains(tmp, "/")) {
        if (OmniDocuGen::Program::StopReq) { break; }
        lvl += "../";
        tmp = tmp.substr(tmp.find("/") + 1);
    }
    if (!lvl.empty()) {
        cfmt = omni::string::replace_all(cfmt, "'../../'", Util::Format("'{0}../../'", lvl));
    }
    for (int32_t i = 1, x = 0; i <= linecnt; ++i, ++x) {
        if (OmniDocuGen::Program::StopReq) { return ""; }
        if (i % 20 == 0) { collapse += "\r\n"; htmllines += "\r\n"; }
        // collapse on: /** .. */ and /* .. */ and { .. }
        tmp = splits[x];
        if ((omni::string::contains(tmp, "class=\"syn_cmt\"") ||
            omni::string::contains(tmp, "class=\"syn_doc\"")) &&
            (omni::string::contains(tmp, "/*") &&
            !omni::string::contains(tmp, "*/"))) {
            //std::string docfmt = "{0}<font class=\"syn_doc\">{1}<div class=\"syn_ex\" id=\"cmnt{2}\" name=\"cmnt{2}\">{3}</div><div></div></font>{4}";
            //std::string cmtfmt = "{0}<font class=\"syn_cmt\">{1}<div class=\"syn_ex\" id=\"cmnt{2}\" name=\"cmnt{2}\">{3}</div><div></div></font>{4}";
            // this is for either 'slash star star' or 'slash star'
            tmp = tmp.substr(tmp.find("id=\"cmnt") + cmsz);
            cmnti = omni::string::util::to_type<int32_t>(tmp.substr(0, tmp.find("\"")));
            cmstr = omni::string::to_string(cmnti);
            if (cmnti > maxcmnt) { maxcmnt = cmnti; }
            htmllines += Util::Format(htfmt, omni::string::pad_left(omni::string::to_string(i), "0", clen), cmstr);
            collapse += Util::Format(cfmt, cmstr);
            for (++i, ++x; i <= linecnt; ++i, ++x) {
                if (OmniDocuGen::Program::StopReq) { return ""; }
                if (i % 20 == 0) { collapse += "\r\n"; htmllines += "\r\n"; }
                htmllines += Util::Format("{0}:<br>", omni::string::pad_left(omni::string::to_string(i), "0", clen));
                collapse += "<br>";
                if (omni::string::contains(splits[x], "*/")) { break; }
            }
            htmllines += "</div>";
            collapse += "</div><div></div>";
            continue;
        }

        /*
        // for now just leave out the {} scope .. comment blocks make it clean enough for now
        if (omni::string::contains(tmp, "{") && !omni::string::contains(tmp, "}")) {
            // this is for either 'slash star star' or 'slash star'
            ++cmnti;
            htmllines += Util::Format(htfmt, i.ToString(dlen), cmnti);
            collapse += Util::Format(cfmt, cmnti);
            continue;
        }
        if (omni::string::contains(tmp, "}") && !omni::string::contains(tmp, "{")) {
            htmllines += "</div>";
            collapse += "</div><div></div>";
        }*/

        htmllines += Util::Format("{0}:<br>", omni::string::pad_left(omni::string::to_string(i), "0", clen));
        collapse += "<br>";
    }
    htmllines += Util::Format("{0}:<br>", omni::string::pad_left(omni::string::to_string(linecnt+1), "0", clen));
    collapse += "<br>";

    switch (clen) {
        case 2: cmstr = "3"; break;
        case 3: cmstr = "3.75"; break;
        case 4: cmstr = "4.3"; break;
        default: break;
    }
    tmp = Util::Format("'{0}', '../../'", omni::string::to_string(maxcmnt));
    if (!lvl.empty()) {
        tmp = omni::string::replace_all(tmp, "'../../'", Util::Format("'{0}../../'", lvl));
    }

    sntx = omni::string::replace_all(sntx, "\r\n", "<br>\r\n") + "<br>";
    sntx = Util::Format(Program::Settings.HtmlViewSyntax, title, htmllines, collapse, cmstr, sntx, tmp);
    sntx = omni::string::replace_all(sntx, "&omninobr;<br>", "");
    if (!lvl.empty()) {
        sntx = omni::string::replace_all(sntx, "=\"../", ("=\"../" + lvl));
        sntx = omni::string::replace_all(sntx, "=\"omni/", Util::Format("=\"{0}omni/", lvl));
        sntx = omni::string::replace_all(sntx, "popup('../../files/src", Util::Format("popup('{0}../../files/src", lvl));
        sntx = omni::string::replace_all(sntx, "href=\"index.html\"", Util::Format("href=\"{0}index.html\"", lvl));
    }
    return sntx;
}

std::string OmniDocuGen::DocuGen::_ColorizePreproc(std::string sntx)
{

    foreach_c (std::string, preproc, Constants::Keywords::Preproc) {
        if (OmniDocuGen::Program::StopReq) { return ""; }
        if (omni::string::contains(sntx, *preproc)) {
            size_t idx = sntx.find(*preproc);
            size_t eidx, fop, efop;
            std::string tmp, tmp1, tmp2;
            while (idx != std::string::npos) {
                if (OmniDocuGen::Program::StopReq) { return ""; }
                eidx = sntx.find("\r\n", idx);
                if (eidx == std::string::npos) { eidx = sntx.size(); }
                tmp = sntx.substr(idx, eidx - idx);
                while (omni::string::ends_with(omni::string::trim(tmp), "\\")) {
                    if (OmniDocuGen::Program::StopReq) { return ""; }
                    eidx = sntx.find("\r\n", eidx + 2);
                    if (eidx == std::string::npos) { eidx = sntx.size(); }
                    tmp = sntx.substr(idx, eidx - idx);
                }
                if (omni::string::contains(tmp, "</font>")) {
                    tmp = omni::string::replace_all(tmp, "</font>", "");
                }
                while (omni::string::contains(tmp, "<font")) {
                    if (OmniDocuGen::Program::StopReq) { return ""; }
                    fop = tmp.find("<font");
                    efop = Util::IndexOfChar(tmp, fop, '>');
                    tmp1 = tmp.substr(0, fop);
                    tmp2 = tmp.substr(efop + 1);
                    tmp = tmp1 + tmp2;
                }
                tmp1 = sntx.substr(0, idx);
                tmp2 = sntx.substr(eidx);
                sntx = tmp1 + "<font class=\"syn_pre\">" + tmp + "</font>" + tmp2;
                idx = sntx.find("</font>", idx + 1);
                idx = sntx.find(*preproc, idx);
                tmp1 = tmp = tmp2 = "";
            }
        }
    }
    return sntx;
}

std::string OmniDocuGen::DocuGen::_ColorizeStrings(const std::string& sntx)
{
    std::string ret = sntx;
    if (omni::string::contains(ret, "&quot;")) {
        int32_t idx = 0;
        int32_t qlen = std::string("&quot;").size();
        List<int32_t> idxs = Util::IndexesOf(sntx, "&quot;");
        bool start = false;
        ret = "";
        for (int32_t i = 0; i < idxs.size(); ++i) {
            if (OmniDocuGen::Program::StopReq) { return ""; }
            if (sntx.substr((((idxs[i] - 1) < 0) ? 0 : (idxs[i] - 1)), 1) == "\\") {
                // is it an escaped string?
                if (((idxs[i] - 2) > 0) && (sntx.substr(idxs[i] - 2, 1) != "\\")) {
                    idxs.erase(idxs.begin()+i);
                    --i;
                    continue;
                }
            }
            if (!start) {
                if (i == 0) {
                    ret += sntx.substr(0, idxs[0]) + "<font class=\"syn_str\">";
                } else {
                    ret += sntx.substr(idx, (idxs[i] - idx)) + "<font class=\"syn_str\">";
                }
                start = true;
            } else {
                ret += sntx.substr(idxs[i - 1], (idxs[i] - idxs[i - 1]) + qlen) + "</font>";
                idx = idxs[i] + qlen;
                start = false;
            }
        }
        if (idxs.size() > 0) {
            ret += sntx.substr(idxs[idxs.size() - 1] + qlen);
        }
    }
    return ret;
}

std::string OmniDocuGen::DocuGen::_ColorizeComments(std::string sntx, bool docmntdiv)
{
    size_t idx, eidx, fop, efop;
    std::string tmp, tmp1, tmp2;
    int32_t cmnti = 0;
    std::string docfmt = "{0}<font class=\"syn_doc\">{1}<div class=\"syn_ex\" id=\"cmnt{2}\" name=\"cmnt{2}\">&omninobr;{3}</div><div></div></font>&omninobr;{4}";
    std::string cmtfmt = "{0}<font class=\"syn_cmt\">{1}<div class=\"syn_ex\" id=\"cmnt{2}\" name=\"cmnt{2}\">&omninobr;{3}</div><div></div></font>&omninobr;{4}";

    int32_t fsz = std::string("</font>").size();
    if (!docmntdiv) {
        docfmt = "{0}<font class=\"syn_doc\">{1}{3}</font>{4}";
        cmtfmt = "{0}<font class=\"syn_cmt\">{1}{3}</font>{4}";
    }
    
    // single line comment (first, incase it's within another comment)
    if (omni::string::contains(sntx, "//")) {
        // single line comment
        idx = sntx.find("//");
        while (idx != std::string::npos) {
            if (Program::StopReq) { break; }
            if (omni::string::contains(sntx, "://") && idx >= 5) {
                if (idx >= 5 && idx - 5 >= 0) { // make sure it's not a http(s)://
                    if (sntx.substr(idx - 5, 7) == "http://") {
                        idx = sntx.find("//", idx + 2);
                        continue;
                    }
                    if (idx > 5 && idx - 6 >= 0) {
                        if (sntx.substr(idx - 6, 8) == "https://") {
                            idx = sntx.find("//", idx + 2);
                            continue;
                        }
                    }
                }
            }
            eidx = sntx.find("\r\n", idx);
            if (eidx == std::string::npos) { eidx = sntx.size(); }
            tmp = sntx.substr(idx, eidx - idx);
            while (omni::string::contains(tmp, "<font")) {
                if (Program::StopReq) { break; }
                fop = tmp.find("<font");
                efop = Util::IndexOfChar(tmp, fop, '>');
                tmp1 = tmp.substr(0, fop);
                tmp2 = tmp.substr(efop + 1);
                fop = tmp2.find("</font>");
                if (fop != std::string::npos) {
                    tmp2 = tmp2.substr(0, fop) + tmp2.substr(fop + fsz);
                }
                tmp = tmp1 + tmp2;
            }
            tmp1 = sntx.substr(0, idx);
            tmp2 = sntx.substr(eidx);
            sntx = tmp1 + "<font class=\"syn_cmt\">" + tmp + "</font>" + tmp2;
            idx = sntx.find("</font>", idx + 1);
            idx = sntx.find("//", idx);
        }
    }
    // doc comment
    if (omni::string::contains(sntx, "/**")) {
        idx = sntx.find("/**");
        int32_t len = 0;
        while (idx != std::string::npos) {
            if (Program::StopReq) { break; }
            eidx = sntx.find("*/", idx);
            len = ((eidx != std::string::npos) && (eidx > 0)) ? ((eidx + 2) - idx) : (sntx.size() - idx);
            if ((sntx.size() < len) || (sntx.size() < (idx + len))) {
                tmp = sntx.substr(idx);
            } else if (len > 0) {
                tmp = sntx.substr(idx, len);
            } else {
                tmp = sntx.substr(idx);
            }
            if (omni::string::contains(tmp, "</font>")) {
                tmp = omni::string::replace_all(tmp, "</font>", "");
            }
            while (omni::string::contains(tmp, "<font")) {
                if (Program::StopReq) { break; }
                fop = tmp.find("<font");
                efop = Util::IndexOfChar(tmp, fop, '>');
                tmp1 = tmp.substr(0, fop);
                tmp2 = tmp.substr(efop + 1);
                tmp = tmp1 + tmp2;
            }
            tmp1 = sntx.substr(0, idx);
            tmp2 = sntx.substr((eidx < 0) ? 0 : (eidx + 2));
            eidx = tmp.find("\r\n");
            if (eidx == std::string::npos) {
                sntx = tmp1 + "<font class=\"syn_doc\">" + tmp + "</font>" + tmp2;
            } else {
                ++cmnti;
                //"{0}<font class=\"syn_doc\">{1}<div class=\"syn_ex\" id=\"cmnt{2}\" name=\"cmnt{2}\">{3}</div><div></div></font>{4}";
                sntx = Util::Format(docfmt, tmp1, tmp.substr(0, eidx), omni::string::to_string(cmnti), tmp.substr(eidx), omni::string::trim_front(tmp2, " "));
            }
            idx = sntx.find("</font>", idx+1);
            idx = sntx.find("/**", idx);
        }
    }
    // multiline line comment
    if (omni::string::contains(sntx, "/*")) {
        idx = sntx.find("/*");
        while (idx != std::string::npos) {
            if (Program::StopReq) { break; }
            if (sntx.substr(idx, 3) == "/**") {
                eidx = sntx.find("*/", idx) + 2;
                idx = sntx.find("/*", eidx);
                continue;
            }
            eidx = sntx.find("*/", idx) + 2;
            tmp = sntx.substr(idx, eidx - idx);
            if (omni::string::contains(tmp, "</font>")) {
                tmp = omni::string::replace_all(tmp, "</font>", "");
            }
            while (omni::string::contains(tmp, "<font")) {
                if (Program::StopReq) { break; }
                fop = tmp.find("<font");
                efop = Util::IndexOfChar(tmp, fop, '>');
                tmp1 = tmp.substr(0, fop);
                tmp2 = tmp.substr(efop + 1);
                tmp = tmp1 + tmp2;
            }
            tmp1 = sntx.substr(0, idx);
            tmp2 = sntx.substr(eidx);
            eidx = tmp.find("\r\n");
            if (eidx == std::string::npos) {
                sntx = tmp1 + "<font class=\"syn_cmt\">" + tmp + "</font>" + tmp2;
            } else {
                ++cmnti;
                //"{0}<font class=\"syn_cmt\">{1}<div class=\"syn_ex\" id=\"cmnt{2}\" name=\"cmnt{2}\">{3}</div><div></div></font>{4}"
                sntx = Util::Format(cmtfmt, tmp1, tmp.substr(0, eidx), omni::string::to_string(cmnti), tmp.substr(eidx), omni::string::trim_front(tmp2, " "));
            }
            idx = sntx.find("</font>", idx + 1);
            idx = sntx.find("/*", idx);
        }
    }
    // doxygen comments keywords
    foreach_c (std::string, dtag, Constants::Keywords::DoxyTags) {
        if (Program::StopReq) { break; }
        if (omni::string::contains(sntx, *dtag)) {
            sntx = omni::string::replace_all(sntx, *dtag, Util::Format("<font class=\"syn_dkw\">{0}</font> ", omni::string::trim(*dtag)));
        }
    }
    return sntx;
}

std::string OmniDocuGen::DocuGen::_RemoveInnerCodeTags(std::string val)
{
    if (omni::string::contains(val, "<code>")) {
        int32_t clen = std::string("<code>").size();
        size_t idx = val.find("<code>");
        int32_t eidx = Util::IndexOfCompliment(val, idx, "<code>", "</code>");
        size_t len = (idx + clen);
        std::string t = val.substr(len, eidx - len);
        while (idx != std::string::npos) {
            if (Program::StopReq) { break; }
            idx += clen;
            if (omni::string::contains(t, "<code>")) {
                t = omni::string::replace_all(t, "<code>", "");
                t = omni::string::replace_all(t, "</code>", "");
                val = (val.substr(0, idx) + t + val.substr(eidx));
            }
            idx = val.find("<code>", idx);
            if (idx == std::string::npos) { break; }
            eidx = Util::IndexOfCompliment(val, idx, "<code>", "</code>");
            if (eidx < 0) { eidx = val.size(); }
            len = (idx + clen);
            t = val.substr(len, eidx - len);
        }
    }
    return val;
}

/// &lt;code&gt; && &lt;/code&gt;
std::string OmniDocuGen::DocuGen::ReplaceHtmlDoxyCodeTags(const std::string& val, const std::string& iref)
{
    std::string r = val;
    std::string t1, t2, t3;
    int32_t idx, idx2;
    int32_t aqsz = std::string("&lt;a href=&quot;").size();
    int32_t ahsz = std::string("&lt;a href=&quot;").size();
    int32_t secsz = std::string("@section ").size();
    // &lt;code&gt; && &lt;/code&gt;
    if (omni::string::contains(r, "&lt;code&gt;")) {
        r = omni::string::replace_all(r, "&lt;code&gt;", "<code>");
        r = omni::string::replace_all(r, "&lt;/code&gt;", "</code>");
    }
    if (omni::string::contains(r, "&lt;/a&gt;")) {
        r = omni::string::replace_all(r, "&lt;/a&gt;", "</a>");
        // &lt;a href=&quot;https://msdn.microsoft.com/en-us/library/ms173171.aspx&quot;&gt;
        while (omni::string::contains(r, "&lt;a href=&quot;")) {
            if (Program::StopReq) { break; }
            idx = r.find("&lt;a href=&quot;") + aqsz;
            idx2 = r.find("&gt;", idx);
            t1 = r.substr(0, idx - ahsz) + "<a href=\"";
            t2 = omni::string::replace_all(r.substr(idx, (idx2 - idx)), "&quot;", "\"") + ">";
            t3 = r.substr(idx2+4);
            r = t1 + t2 + t3;
        }
    }
    while (omni::string::contains(r, "@c ")) {
        if (Program::StopReq) { break; }
        idx = r.find("@c ") + 3; // <code>
        idx2 = Util::IndexOfWsChar(r, idx);
        if (idx2 < 0) {
            idx2 = r.size();
        }
        t1 = r.substr(0, idx - 3);
        t2 = "<code>" + r.substr(idx, (idx2 - idx)) + "</code>";
        t3 = r.substr(idx2);
        r = t1 + t2 + t3;
    }
    while (omni::string::contains(r, "@h ")) {
        if (Program::StopReq) { break; }
        idx = r.find("@h ") + 3; // "@source ".size();
        idx2 = Util::IndexOfWsChar(r, idx);
        t1 = r.substr(0, idx - 3);
        t2 = r.substr(idx, (idx2 - idx));
        t2 = Util::Format("<a href=\"{0}{1}.html\" class=\"code\">{1}</a>", iref, t2);
        t3 = r.substr(idx2 + 3);
        r = t1 + t2 + t3;
    }
    while (omni::string::contains(r, "@i ")) {
        if (Program::StopReq) { break; }
        idx = r.find("@i ") + 3; // "@source ".size();
        idx2 = r.find(" @i", idx);
        t1 = r.substr(0, idx - 3);
        t2 = Util::Format("<i>{0}</i>", r.substr(idx, (idx2 - idx)));
        t3 = r.substr(idx2 + 3);
        r = t1 + t2 + t3;
    }
    while (omni::string::contains(r, "@b ")) {
        if (Program::StopReq) { break; }
        idx = r.find("@b ") + 3; // "@source ".size();
        idx2 = r.find(" @b", idx);
        t1 = r.substr(0, idx - 3);
        t2 = Util::Format("<b>{0}</b>", r.substr(idx, (idx2 - idx)));
        t3 = r.substr(idx2 + 3);
        r = t1 + t2 + t3;
    }
    while (omni::string::contains(r, "@section ")) {
        if (Program::StopReq) { break; }
        idx = r.find("@section ") + secsz;
        idx2 = r.find("\r\n", idx);
        t1 = r.substr(0, idx - secsz);
        t2 = Util::Format("<font class=\"hdr\">{0}</font>", r.substr(idx, (idx2 - idx)));
        t3 = r.substr(idx2);
        r = t1 + t2 + t3;
    }
    return DocuGen::_RemoveInnerCodeTags(r);
}

/// Replaces the #include omni_file with #include href="" omni_file
/// <param name="sntx">The code</param>
/// <param name="inchref">The reletiave path to the htmlsrc dir (i.e. "../htmlsrc/")</param>
/// <returns></returns>
std::string OmniDocuGen::DocuGen::ReplaceIncludes(std::string sntx, std::string inchref)
{
    if (!inchref.empty() && !omni::string::ends_with(inchref, "/")) { inchref += "/"; }
    std::string line, tmp, nm;
    //std::string oahfmt = "#include &lt;<a href=\"" + inchref + "{0}.html\">{0}</a>&gt;";
    std::string oahfmt = "<a href=\"" + inchref + "{0}.html\">{0}</a>";
    std::string oinc = "#include &lt;omni";
    size_t pos, epos, len, tpos;
    pos = sntx.find(oinc);
    while (pos != std::string::npos) {
        pos = sntx.find("omni", pos);
        epos = sntx.find("&gt;", pos);
        if (epos == std::string::npos) { epos = sntx.size(); }
        len = epos - pos;
        nm = sntx.substr(pos, len);
        if (!omni::io::file::exists(omni::io::path::combine(Program::Settings.SourceDirectory, nm))) {
            up(4, "Include '{0}' doesn't exists in the source directory.", nm);
        }
        tmp = Util::Format(oahfmt, nm);
        sntx.replace(pos, len, tmp);
        pos = sntx.find(oinc, sntx.find("&gt;", pos));
    }
    return sntx;
}

/// <param name="val"></param>
/// <param name="lvl"></param>
/// <returns></returns>
std::string OmniDocuGen::DocuGen::ReplaceMacroInfo(const std::string& val, const std::string& lvl, bool codeTags)
{
    if (val.empty()) { return val; }
    std::string r = val;
    std::string beg = ""; std::string end = "";
    if (codeTags) { beg = "<code>"; end = "</code>"; }
    foreach (MacroOp, op, DocuGen::Macros) {
        if (OmniDocuGen::Program::StopReq) { return ""; }
        r = Util::ReplaceAll(r, op->Name,
            (beg + "<a href=\"" + lvl + omni::string::to_lower(op->Name) + ".html\">" + op->Name + "</a>" + end)
        );
    }
    return r;
}

/// 
/// <param name="val"></param>
/// <param name="lvl"></param>
/// <returns></returns>
std::string OmniDocuGen::DocuGen::ReplaceSysApiInfo(const std::string& val, bool codeTags)
{
    if (val.empty()) { return val; }
    std::string r = val;
    std::string beg = ""; std::string end = "";
    if (codeTags) { beg = "<code>"; end = "</code>"; }
    foreach (SysAPI, api, DocuGen::SysAPIs) {
        if (OmniDocuGen::Program::StopReq) { return ""; }
        r = Util::ReplaceAll(r, api->Name, (beg + "<a href=\"" + api->Link + "\">" + api->Name + "</a>" + end));
        if (api->SysType == Types::SystemType::Windows) {
            r = Util::ReplaceAll(r, (api->Name + "A"), (beg + "<a href=\"" + api->Link + "\">" + api->Name + "A</a>" + end));
            r = Util::ReplaceAll(r, (api->Name + "W"), (beg + "<a href=\"" + api->Link + "\">" + api->Name + "W</a>" + end));
        }
    }
    return r;
}

std::string OmniDocuGen::DocuGen::ReplaceKeywords(const std::string& code, bool hasq, bool hasnc)
{
    // replace types first, becuase the types keywords have "class", which is in <font class
    // and confuses the linter, so just have "class" be the first thing to be replaced ;) .. 
    // hey .. sometimes stupid hacks work alright!
    std::string sntx = code;
    // types
    foreach_c (std::string, kw, Constants::Keywords::Types) {
        if (OmniDocuGen::Program::StopReq) { return ""; }
        if (!omni::string::contains(code, *kw)) { continue; } // code doesn't contain a keyword, continue
        sntx = Util::ReplaceAll(sntx, *kw, ("<font class=\"syn_typ\">" + *kw + "</font>"));
    }
    // instructions
    foreach_c (std::string, kw, Constants::Keywords::Instructions) {
        if (OmniDocuGen::Program::StopReq) { return ""; }
        if (!omni::string::contains(code, *kw)) { continue; } // code doesn't contain a keyword, continue
        sntx = Util::ReplaceAll(sntx, *kw, ("<font class=\"syn_ins\">" + *kw + "</font>"));
    }
    sntx = omni::string::replace_all(sntx, "#<font class=\"syn_ins\">if</font>", "#if");
    sntx = omni::string::replace_all(sntx, "#<font class=\"syn_ins\">else</font>", "#else");

    // numbers
    sntx = replace_nums(sntx);
    if (hasq) { sntx = omni::string::replace_all(sntx, "&#<font class=\"syn_num\">39</font>;", "&#39;"); }
    if (hasnc) { sntx = omni::string::replace_all(sntx, "&#39;\\<font class=\"syn_num\">0</font>&#39;", "&#39;\\0&#39;"); }
    
    // chars
    try {
        sntx = replace_chars(sntx);
    } catch (const std::exception& ex) {
        Program::AddError(ex, "replace_chars, check for '");
    }

    // operators (no highlight for now .. it's nice-ish, but meh, too much headache)
    //sntx = Replace(sntx, "\\b([\\=\\-\\+\\*\\&\\^\\%\\!\\~\\|\\<\\>\\/]=)\\b", "<font class=\"syn_opr\">$1</font>");
    //sntx = Replace(sntx, "\\b(\\|\\||\\&\\&|\\+\\+|\\-\\-|\\%|\\!|\\~)\\b", "<font class=\"syn_opr\">$1</font>");
    return sntx;
}

// HTML Gen Functions

/// Gets an html file tree
/// <param name="verbose">true to incldue file info</param>
/// <returns></returns>
std::string OmniDocuGen::DocuGen::GetFileTree(bool verbose, bool isPlainText)
{
    std::string ftree = "";
    omni::seq::std_string_t dirs, files;
    omni::io::directory::get_directories(Program::Settings.SourceDirectory, dirs);
    omni::io::directory::get_files(Program::Settings.SourceDirectory, files);
    std::sort(dirs.begin(), dirs.end());
    std::sort(files.begin(), files.end(), DocuGen::_CompareFileNames);
    std::string extol = omni::string::to_lower(Program::Settings.Excluded);
    foreach_t (omni::seq::std_string_t, subd, dirs) {
        if (OmniDocuGen::Program::StopReq) { return ""; }
        if (omni::string::contains(extol, omni::string::to_lower(*subd))) { continue; }
        ftree += DocuGen::_GetFolderViewTplate(*subd, Program::Settings.SourceDirectory, verbose, isPlainText);
    }
    ftree += "\r\n";
    std::string ext;
    foreach_t (omni::seq::std_string_t, fl, files) {
        if (OmniDocuGen::Program::StopReq) { return ""; }
        if (omni::string::contains(extol, omni::string::to_lower(*fl))) { continue; }
        if (omni::io::path::get_extension(*fl).empty() && (omni::io::path::get_name(*fl) != "omnilib")) { continue; }
        ftree += DocuGen::_GetFileViewTplate(*fl, Program::Settings.SourceDirectory, verbose, false, isPlainText);
    }
    return ftree;
}

/// Find and replace the member info for each specific member type info
/// <param name="mti">The member type to search</param>
/// <param name="val">The std::string to search</param>
/// <returns>The replaced string</returns>
std::string OmniDocuGen::DocuGen::ReplaceMemberInfo(MemberTypeInformation::ptr_t& mti, const std::string& val, const std::string& lvl, bool codeTags)
{
    /* we're parsing member info and looking for exact matches. If the member
     * has anything at the end of the std::string other than a whitespace or an open
     * paren, chances are it's not what we're looking for (i.e. a similarly named
     * member). Example: omni::delegate::operator ! will match omni::delegate::operator !=
     * but they're obviously not the same. An open paren '(' means it's a function and
     * thus the member we're looking for; an empty std::string means it's on a word boundry
     * and again, what we're looking for; as well the semi-colon ';' if found could mean
     * it's a typedef or something of the nature (or the end of statement), thus, again,
     * what we're looking for.
     */
    if (!mti) { return val; }
    std::string r = val;
    foreach (MemberTypeInformation::ptr_t, m, mti->Members) {
        if (OmniDocuGen::Program::StopReq) { return ""; }
        r = DocuGen::ReplaceMemberInfo(*m, r, lvl, codeTags);
    }
    if (mti->FullPath != "omni") {
        std::string fmt = mti->FullPath;
        if (omni::string::contains(val, fmt)) {
            std::string fullPath = fmt;
            std::string fpath = mti->GetFilePath();
            std::string cfmt = "<a href=\"{0}{1}.html\">";
            std::string afmt = "</a>";
            if (codeTags) {
                cfmt = "<code>" + cfmt;
                afmt += "</code>";
            }
            size_t idx = r.find(fullPath);
            int32_t tlen = fullPath.size();
            while (idx != std::string::npos) {
                if (OmniDocuGen::Program::StopReq) { return ""; }
                fmt = "";
                if ((idx + tlen + 1) <= r.size()) {
                    fmt = omni::string::trim(omni::string::replace(r.substr(idx, tlen + 1), fullPath, ""));
                    if (fmt == "(" || fmt == ")" || fmt == ";" ||
                        fmt == "," || fmt == "[" || fmt == "/" ||
                        fmt == "." || fmt == "&" || fmt == "*") { fmt = ""; }
                    if ((fmt == "<") && ((idx + tlen + 7) < r.size()) && (r.substr(idx + tlen, 7) == "<a href")) {
                        fmt = "";
                    }
                }
                if (fmt.empty()) {
                    fmt = Util::Format(cfmt, lvl, fpath);
                    r = r.substr(0, idx) + fmt + fullPath + afmt + r.substr(idx + tlen);
                    idx = (idx + fmt.size() + tlen + afmt.size());
                } else {
                    if (fmt != ":" && fmt != "_" && !omni::char_util::is_alpha_digit(fmt[0])) {
                        Program::AddError(Util::Format("Check it: {0} -> {1}", fmt, fullPath));
                    }
                    idx = (idx + tlen);
                }
                idx = r.find(fullPath, idx);
            }
        }
    }
    return r;
}

std::string OmniDocuGen::DocuGen::GetHTMLTree(MemberTypeInformation::ptr_t& mti, bool includePrivate)
{
    if (!mti || mti->CodeType == OmniDocuGen::Types::CodeStructureType::Unknown) { return ""; }
    if (mti->FullPath == "" || mti->Name == "") {
        if (mti->Level != 0 && mti->Name != "omni") {
            return "";
        }
    }
    std::string r;
    std::string ct;
    std::string tt;
    std::string tmp;
    std::string tb = "    ";
    std::string nl = "\r\n";
    std::string ident = tb;
    std::string nm = Util::ToFilePath(mti->FullPath);
    for (int i = 1; i < mti->Level; i++) {
        ident += tb;
    }
    if (mti->Parent) {
        ident += tb;
    }
    // ns, cls, tdef, fn, mbr, strct, eval, file
    ct = omni::string::to_lower(Util::ToString(mti->CodeType, true));
    if (mti->Comment && !mti->Comment->Synopsis.empty()) {
        tt = omni::string::replace_all(mti->Comment->Synopsis, "@c ", "");
        tt = omni::string::replace_all(tt, "<code>", "");
        tt = omni::string::replace_all(tt, "</code>", "");
        tt = Util::Format("{0}: {1} - {2}", omni::string::to_lower(Util::ToString(mti->CodeType, false)), mti->FullPath, tt);
    } else {
        tt = Util::Format("{0}: {1}", omni::string::to_lower(Util::ToString(mti->CodeType, true)), mti->FullPath);
    }
    if ((mti->CodeType == OmniDocuGen::Types::CodeStructureType::Namespace && !mti->IsNamespaceAlias()) ||
        mti->CodeType == OmniDocuGen::Types::CodeStructureType::Class ||
        mti->CodeType == OmniDocuGen::Types::CodeStructureType::Struct ||
        mti->CodeType == OmniDocuGen::Types::CodeStructureType::Enum)
    {
        r += Util::Format("{0}<li class=\"{1}\" title=\"{2}\">{3}", ident, ct, tt, nl);
        ident += tb;
        r += Util::Format("{0}<input type=\"checkbox\" id=\"{1}_{2}\" name=\"{1}_{2}\"{3} />{4}", ident, nm, ct, (mti->Level == 0 ? " checked" : ""), nl);
        r += Util::Format("{0}<label for=\"{1}_{2}\"><a href=\"{1}.html\">{3}</a></label>{4}", ident, nm, ct, mti->Name, nl);
        r += Util::Format("{0}<ol id=\"{2}_{1}\" name=\"{2}_{1}\">{3}", ident, nm, ct, nl);
        foreach (MemberTypeInformation::ptr_t, mti2, mti->Members) {
            if (OmniDocuGen::Program::StopReq) { return ""; }
            if (!includePrivate && (*mti2)->ScopeAccessType == OmniDocuGen::Types::CodeScopeAcessType::Private) { continue; }
            r += DocuGen::GetHTMLTree(*mti2, includePrivate);
        }
        r += Util::Format("{0}</ol>{1}", ident, nl);
        ident = ident.substr(0, ident.length() - tb.length());
        r += Util::Format("{0}</li>", ident);
    } else {
        //ident += tb;
        r += Util::Format("{0}<li class=\"{1}\" title=\"{2}\">", ident, ct, tt);
        r += Util::Format("<a href=\"{0}.html\">{1}</a></li>", nm, mti->Name);
    }
    r += nl;
    return r;
}

/// Generates the classes.html file
/// <param name="mti">The member list to use</param>
/// <param name="outdir">The output directory to use</param>
void OmniDocuGen::DocuGen::GenerateClassesIndexHtml(const std::string& classdir, MemberTypeInformation::ptr_t& allmti)
{
    up("Generating classes.html");
    //std::string ofile = Path.Combine(classdir, "index.html");
    std::string chtml = Program::Settings.HtmlClasses;
    std::string tree = DocuGen::GetHTMLTree(allmti, false);
    std::string html = omni::string::replace(chtml, "<!-- INSERT TREE HERE -->", tree);
    if (Util::WriteFile(OutPaths::ClassIndexHtml, html)) {
        if (DocuGen::DoHashZipFiles) {
            html = replace_dl_html(html);
            Util::WriteFile(OutPaths::TempClassIndexHtml, html);
        }
        up("Wrote {0}", OutPaths::ClassIndexHtml);
    } else {
        up("Could not write {0}", OutPaths::ClassIndexHtml);
    }
}

/// Does things
    /// <param name="code">The code to highlight</param>
    /// <param name="inchref">The relative path to the 'htmlsrc' dir (i.e. "../")</param>
    /// <param name="dochref">The relative path to the 'options' dir (i.e. "../") </param>
    /// <param name="allmti">The members to reference (can be NULL)</param>
    /// <param name="docmntdiv">True to add the line number division for any comments</param>
std::string OmniDocuGen::DocuGen::GenerateHtmlSyntaxHighlight(const std::string& code, const std::string& inchref, const std::string& dochref, MemberTypeInformation::ptr_t& allmti, bool docmntdiv)
{
    std::string sntx = InternalGenerateHtmlSyntaxHighlight(code, inchref, dochref, allmti, docmntdiv, "htmlsrc/");
    sntx = omni::string::replace_all(sntx, "    ", "\t");
    sntx = omni::string::replace_all(sntx, "\t", "&nbsp;&nbsp;&nbsp;&nbsp;");
    return sntx;
}

/// Generates syntax highlighted HTML code
    /// <param name="srcfile">The source file</param>
    /// <param name="code">The code to HTML-ify</param>
    /// <param name="allmti">The member info to 'link' against (if any)</param>
    /// <param name="dochref">The href level (../../, etc.) for the 'allmti'</param>
    /// <param name="inchref">The include level</param>
    /// <param name="docmntdiv">True to add the line number division for any comments</param>
std::string OmniDocuGen::DocuGen::GenerateHtmlSyntaxHighlight(const std::string& srcfile, const std::string& code, MemberTypeInformation::ptr_t& allmti, const std::string& dochref, const std::string& inchref, bool docmntdiv)
{
    std::string sntx = InternalGenerateHtmlSyntaxHighlight(code, inchref, dochref, allmti, docmntdiv, "");
    // generate the member anchors
    sntx = DocuGen::_GenerateMemberHtmlNameAnchors(srcfile, sntx, allmti);
    // generate the HTML from the template
    sntx = DocuGen::_GenerateHtmlSyntaxFromTemplate(
                    (srcfile.substr(srcfile.rfind("\\") + 1)), // name
                    omni::string::replace_all(omni::string::replace(srcfile, Program::Settings.SourceDirectory, ""), "\\", "/"), // title
                    sntx); // code
    return sntx;
}

std::string OmniDocuGen::DocuGen::_GenerateMemberHtmlNameAnchors(const std::string& srcfile, const std::string& html, MemberTypeInformation::ptr_t& m)
{
    std::string r = html;
    foreach (MemberTypeInformation::ptr_t, mi, m->Members) {
        if (OmniDocuGen::Program::StopReq) { return ""; }
        r = DocuGen::_GenerateMemberHtmlNameAnchors(srcfile, r, *mi);
    }
    int32_t cnt = 0;
    size_t idx = std::string::npos;
    if ((m->HeaderFile == srcfile) && (m->HeaderLine >= 0)) {
        idx = html.find("\r\n");
        while ((idx != std::string::npos) && (++cnt < m->HeaderLine-1)) {
            idx = r.find("\r\n", (idx + 1)); // r.IndexOfString(idx + 2, "\r\n");
        }
    } else if ((m->ImplFile == srcfile) && (m->SourceImplLine >= 0)) {
        idx = html.find("\r\n");
        while ((idx != std::string::npos) && (++cnt < m->SourceImplLine-1)) {
            idx = r.find("\r\n", (idx + 2)) ; // r.IndexOfString(idx + 2, "\r\n");
        }
    }
    return ((idx == std::string::npos) ? r : r.insert(idx+2, Util::Format("<a name=\"{0}\"></a>", m->FullPath)));
}

std::string OmniDocuGen::DocuGen::GenerateHtmlClassHelp(MemberTypeInformation::ptr_t& mti)
{
    try {
        std::string srcdir = Program::Settings.SourceDirectory;
        if (!omni::string::ends_with(srcdir, OMNI_PATH_SEPARATOR)) { srcdir += OMNI_PATH_SEPARATOR; }
        std::string ifile = omni::string::replace_all(omni::string::replace(mti->ImplFile, srcdir, ""), "\\", "/");
        std::string hsrcdir = omni::string::replace_all(omni::string::replace(DocuGen::HtmlSyntax, DocuGen::Docs, ""), "\\", "/");
        std::string ctype = omni::string::to_lower(Util::ToString(mti->CodeType, false));
        std::string sig = "";
        if ((mti->Parent) && Util::IsFunction(mti->CodeType) && Util::IsClassOrStruct(mti->Parent->CodeType)) {
            ctype = Util::Format("member {0}", ctype);
        }
        if (mti->IsStatic || ((mti->Parent) && Util::IsFunction(mti->CodeType) && Util::IsNamespace(mti->Parent->CodeType))) {
            ctype = Util::Format("{0}", ctype);
        }
        if (Util::IsProtected(mti->ScopeAccessType)) {
            ctype = Util::Format("protected {0}", ctype);
        }
        if (ifile.empty()) { ifile = Util::ToFilePath(mti->FullPath); }
        if (!mti->Signature.empty()) {
            std::string tnm, tret, tsig, tsyn;
            size_t fppos, len;
            sig = Util::Format("<code>{0}</code>", DocuGen::GenerateHtmlSyntaxHighlight(mti->Include, "../", "../", DocuGen::AllMti, false));
            if (mti->Members.size() > 0) {
                sig += "<br><code>" + omni::string::to_lower(Util::ToString(mti->CodeType, false)) + " " + mti->FullPath + "</code>";
                //sig += Util::Format("<br><code>{0}</code>", DocuGen::GenerateHtmlSyntaxHighlight(mti->Signature, "../", "../", DocuGen::AllMti, false));
                sig += "\r\n\r\n<font class=\"docu\">MEMBERS</font>\r\n\r\n<code>";
                try {
                    foreach_c (MemberTypeInformation::ptr_t, o, mti->Members) {
                        if (OmniDocuGen::Program::StopReq) { return ""; }
                        if (Util::IsPrivate((*o)->ScopeAccessType)) { continue; }
                        if (Util::IsFunction((*o)->CodeType)) {
                            sig += DocuGen::GenerateHtmlSyntaxHighlight((*o)->Signature, "../", "../", DocuGen::AllMti, false) + "\r\n";
                        } else {
                            sig += DocuGen::GenerateHtmlSyntaxHighlight((*o)->FullPath, "../", "../", DocuGen::AllMti, false) + "\r\n";
                        }
                    }
                } catch (const std::exception& ex) {
                    Program::AddError(ex, "HTML member error");
                }
                sig = omni::string::replace_all(sig, "\r\n", "<br>\r\n") + "</code>";
            } else {
                fppos = mti->Signature.find(mti->FullPath);
                len = mti->FullPath.size();
                if (fppos == std::string::npos) {
                    fppos = mti->Signature.find(mti->Name);
                    len = mti->Name.size();
                }
                // get return
                tret = mti->Signature.substr(0, fppos);
                tret = DocuGen::GenerateHtmlSyntaxHighlight(tret, "../", "../", DocuGen::AllMti, false);
                if (!tret.empty()) { tret += " "; }
                // get name
                tnm = mti->Signature.substr(fppos, len);
                //tnm = Util::Format("<a href=\"../classes/{0}.html\">{1}</a>", (*o)->GetFilePath(), tnm);
                // get "signature"
                tsig = mti->Signature.substr(fppos + len);
                tsig = DocuGen::GenerateHtmlSyntaxHighlight(tsig, "../", "../", DocuGen::AllMti, false);
                sig += "<br><code>" + tret + tnm + tsig + "</code>\r\n";
                //sig += Util::Format("<br><code>{0}</code>", DocuGen::GenerateHtmlSyntaxHighlight(mti->Signature, "../", "../", DocuGen::AllMti, false));
            }
            if (mti->IsOverloaded()) {
                sig += "\r\n\r\n<font class=\"docu\">OVERLOADS</font>\r\n\r\n<code>";
                try {
                    foreach (MemberTypeInformation::ptr_t, o, mti->Overloads) {
                        if (OmniDocuGen::Program::StopReq) { return ""; }
                        fppos = (*o)->Signature.find((*o)->FullPath);
                        len = (*o)->FullPath.size();
                        if (fppos == std::string::npos) {
                            fppos = (*o)->Signature.find((*o)->Name);
                            len = (*o)->Name.size();
                        }
                        // get return
                        tret = (*o)->Signature.substr(0, fppos);
                        tret = DocuGen::GenerateHtmlSyntaxHighlight(tret, "../", "../", DocuGen::AllMti, false);
                        if (!tret.empty()) { tret += " "; }
                        // get name
                        tnm = (*o)->Signature.substr(fppos, len);
                        tnm = Util::Format("<a href=\"../classes/{0}.html\">{1}</a>", (*o)->GetFilePath(), tnm);                        
                        // get "signature"
                        tsig = (*o)->Signature.substr(fppos + len);
                        tsig = DocuGen::GenerateHtmlSyntaxHighlight(tsig, "../", "../", DocuGen::AllMti, false);

                        sig += tret + tnm + tsig + "\r\n";
                    }
                } catch (const std::exception& ex) {
                    Program::AddError(ex, "HTML overload error");
                }
                sig = omni::string::replace_all(sig, "\r\n", "<br>\r\n") + "</code>";
            }
        }
        List<std::string> vals;
        vals.push_back(Util::Format("{0}: {1}", ctype, mti->FullPath));
        vals.push_back(mti->FullPath);
        vals.push_back(Util::Format("<a href=\"..{0}/{1}.html#{2}\" class=\"chnm\">\r\n    {2}\r\n    </a>", hsrcdir, ifile, mti->FullPath));
        vals.push_back(((!mti->Parent) ? "" : Util::Format("<br>A {0} of <a href=\"{2}.html\" class=\"code\">{1}</a><br>", ctype, mti->Parent->FullPath, Util::ToFilePath(mti->Parent->FullPath))));
        if (!sig.empty()) {
            vals[3] = Util::Format("{0}<br>\r\n    {1}", vals[3], omni::string::replace_all(sig, "\r\n","\r\n    "));
        }
        omni::sequence::add_range(vals, mti->Comment->HtmlList());
        /*
            // this is the index list .. easier to modify the template than move index around
            // 0 - title (full path)
            // 1 - header (full path)
            // 2 - name (takes to htmlsrc)
            // 3 - a blank of x && #include<> && sig + members/overloads
            // mti->Comment.HtmlList() gives the following:
            // 4 - synopsis (@brief)
            // 5 - desc (@details)
            // 6 - params (if any) (@param/@tparam)
            // 7 - example
            // 8 - return (if any) (@return)
            // 9 - error (if any) (@exception)
            // 10 - consider (if any) (@warning)
            // 11 - platform (if any) (@attention)
            // 12 - notes (if any) (@note)
            // 13 - complexity (if any) (@invariant)
            * layout
            * @brief          Brief description.
            * @details        A more detailed description of the function.
            * @return         [optional] A return value if any.
            * @param [name]   [optional] Each parameter should be marked with this.
            @tparam [name]  [optional] Each template parameter should be marked with this.
            * @exception      [optional] Any errors (or error conditions) specific to this context.
            * @warning        [optional] Any extra considerations to be aware of.
            * @attention      [optional] Any platform specific notes.
            * @note           [optional] Any notes to be aware of (like system calls, order of operations, etc.).
            * @invariant      [optional] This is the complexity of this function (e.g. O(1) for X conditions, etc.)
            */
        for (int32_t i = 0; i < vals.size(); ++i) {
            vals[i] = omni::string::trim(vals[i]);
        }
        return Util::Format(Program::Settings.HtmlClassTemplate,
            vals[0], vals[1], vals[2], vals[3], vals[4], vals[5], vals[6],
            vals[7], vals[8], vals[9], vals[10], vals[11], vals[12], vals[13]);
    } catch (const std::exception& ex) {
        Program::AddError(ex, Util::Format("HTML general error for {0} in '{1}'", mti->FullPath, mti->OwnerSourceFile));
    }
    return (!mti ? "" : static_cast<std::string>(*mti));
}

/// Generates the HTML class help document (classes/omni@@name.html)
void OmniDocuGen::DocuGen::GenerateHtmlClassHelp(const std::string& classdir, MemberTypeInformation::ptr_t& mti, bool recurse)
{
    if (mti) {
        if (!Util::IsPrivate(mti->ScopeAccessType)) {
            std::string fpath = mti->GetFilePath();
            std::string fname = omni::io::path::combine(classdir, (fpath + ".html"));
            std::string html = DocuGen::GenerateHtmlClassHelp(mti);
            if (OmniDocuGen::Program::StopReq) { return; }
            Util::WriteFile(fname, html);
            if (DocuGen::DoHashZipFiles) {
                html = replace_dl_html(html);
                Util::WriteFile(omni::string::replace(fname, DocuGen::Root, OutPaths::TempOut), html);
            }
            Program::AddGeneratedHelpFile(fpath);
            foreach (MemberTypeInformation::ptr_t, m, mti->Overloads) {
                if (OmniDocuGen::Program::StopReq) { return; }
                DocuGen::GenerateHtmlClassHelp(classdir, *m, recurse);
            }
            if (recurse) {
                foreach (MemberTypeInformation::ptr_t, m, mti->Members) {
                    if (OmniDocuGen::Program::StopReq) { return; }
                    DocuGen::GenerateHtmlClassHelp(classdir, *m, true);
                }
            }
            up(2, "HTML: {0} - {1}", mti->Name, mti->FullPath);
        } else {
            up(2, "Ignoring private member: {0} - {1}", mti->Name, mti->FullPath);
        }
        // else { Program::AddError("Not generating html class help for private member: " + mti->FullPath); }
    }
}

/// Generates the HTML based on the code read from the source file
/// <param name="code">The code read from source file</param>
/// <param name="finfo">The fileinfo object</param>
void OmniDocuGen::DocuGen::GenerateHtmlSyntax(CodeGen::ptr_t& c)
{
    up(1, "Generating HTML for {0}", c->Name());
    std::string title = omni::string::replace_all(omni::string::replace(c->SourceFile, Program::Settings.SourceDirectory, ""), "\\", "/");
    std::string html = DocuGen::GenerateHtmlSyntaxHighlight(c->SourceFile, c->SourceSansComment(), DocuGen::AllMti, "../", "", true);
    if (Util::WriteFile(c->HtmlSyntaxFile, html)) {
        if (DocuGen::DoHashZipFiles) {
            html = replace_dl_html(html);
            Util::WriteFile(omni::string::replace(c->HtmlSyntaxFile, DocuGen::Root, OutPaths::TempOut), html);
        }
        up("Generated {0}", c->HtmlSyntaxFile);
    } else {
        up("Could not generate {0}", c->HtmlSyntaxFile);
    }
}

/// Generates the files.html file
void OmniDocuGen::DocuGen::GenerateFilesViewHtml()
{
    Program::SetGenerationProgress(Types::GenerationStatus::FileViewStart);
    try {
        up("Generating {0} and {1}", OutPaths::HtmlSrcIndexHtml, OutPaths::FilesIndexHtml);
        Util::CheckAndCreateDir(DocuGen::FilesSource);
        
        // copy "raw" source to "undocumented" source
        std::string rname = "";
        foreach (CodeGen::ptr_t, c, DocuGen::CodeGenList) {
            if (OmniDocuGen::Program::StopReq) { return; }
            rname = omni::string::replace_all((*c)->SourceFile, Program::Settings.SourceDirectory, DocuGen::FilesSource);
            up(2, "Copying non-commented source {0} to {1}", (*c)->SourceFile, rname);
            Util::WriteFile(rname, (*c)->SourceSansComment());
        }
        Util::CopyFile(
            omni::io::path::combine(Program::Settings.SourceDirectory, "omnilib"),
            omni::io::path::combine(DocuGen::FilesSource, "omnilib"),
            false
        );
        //Util::CopyDirectory(Program::Settings.SourceDirectory, DocuGen::FilesSource, true, true);
        Util::WriteRedirectDirectories(DocuGen::FilesSource, "index.html", 1);
        Util::CopyDirectory(DocuGen::FilesSource, omni::string::replace(DocuGen::FilesSource, DocuGen::Root, OutPaths::TempOut), true, true);
        // write the htmlsrc/index.html
        std::string ftree = DocuGen::GetFileTree(true, false);
        std::string html = omni::string::replace(Program::Settings.HtmlView, "<!-- INSERT FILE TREE HERE -->", ftree);
        Util::WriteFile(OutPaths::HtmlSrcIndexHtml, html);
        if (DocuGen::DoHashZipFiles) {
            html = replace_dl_html(html);
            Util::WriteFile(OutPaths::TempHtmlSrcIndexHtml, html);
        }
        // modify file view tree for the files/index.html
        ftree = DocuGen::GetFileTree(true, true);
        html = omni::string::replace(Program::Settings.HtmlFilesIndex, "<!-- INSERT FILE TREE HERE -->", ftree);
        Util::WriteFile(OutPaths::FilesIndexHtml, html);
        if (DocuGen::DoHashZipFiles) {
            html = replace_dl_html(html);
            Util::WriteFile(OutPaths::TempFilesIndexHtml, html);
        }
    } catch (const std::exception& ex) {
        Program::AddError(ex, "Files view error");
    }
    Program::SetGenerationProgress(Types::GenerationStatus::FileViewComplete);
}

std::string OmniDocuGen::DocuGen::ReplaceFrameworkInfo(const std::string& val, const std::string& mihref, const std::string& dhref, const std::string& fref)
{
    if (val.empty()) { return val; }
    std::string r = Util::ToHTML(val);
    r = DocuGen::ReplaceMemberInfo(DocuGen::AllMti, r, mihref, true);
    r = DocuGen::ReplaceMacroInfo(r, dhref, true);
    r = DocuGen::ReplaceSysApiInfo(r, true);
    r = DocuGen::ReplaceHtmlDoxyCodeTags(r, fref + "htmlsrc/");
    r = DocuGen::ReplaceIncludes(r, fref + "htmlsrc/");
    r = omni::string::replace_all(r, "    ", "\t");
    r = omni::string::replace_all(r, "\t", "&nbsp;&nbsp;&nbsp;&nbsp;");
    return omni::string::replace_all(r, "\r\n", "<br>\r\n");
}
