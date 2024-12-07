#include "docugen.hpp"

using namespace OmniDocuGen;

/// Sorts the delegates in numerical (v. alphabetical) order, such
/// that they appear as delegate1, delegate2 ... delegate10, and not
/// delegate1, delegate10 ... delegate2
void OmniDocuGen::DocuGen::_SortSourceAndDelegateHeaders()
{
    up(1, "Sorting source...");
    std::sort(OmniDocuGen::DocuGen::SourceFiles.begin(), OmniDocuGen::DocuGen::SourceFiles.end());
    std::sort(OmniDocuGen::DocuGen::HeaderFiles.begin(), OmniDocuGen::DocuGen::HeaderFiles.end());
    List<std::string> dheaders;
    int32_t iidx = -1;
    for (int32_t i = 0; i < OmniDocuGen::DocuGen::HeaderFiles.size(); ++i) {
        if (OmniDocuGen::Program::StopReq) { return; }
        if (omni::string::contains(OmniDocuGen::DocuGen::HeaderFiles[i], "delegate")) {
            if (iidx < 0) { iidx = i; }
            dheaders.push_back(OmniDocuGen::DocuGen::HeaderFiles[i]);
            OmniDocuGen::DocuGen::HeaderFiles.erase(OmniDocuGen::DocuGen::HeaderFiles.begin() + i);
            --i;
        }
    }
    std::sort(dheaders.begin(), dheaders.end());
    std::string tmp, n1, n2;
    int32_t dlen = std::string("delegate").size();
    size_t idx1, idx2, x, y;
    for (x = 0; x < dheaders.size(); ++x) {
        if (OmniDocuGen::Program::StopReq) { return; }
        if (omni::string::contains(dheaders[x], "delegates")) { continue; }
        for (y = 0; y < dheaders.size() - 1; ++y) {
            if (OmniDocuGen::Program::StopReq) { return; }
            if (omni::string::contains(dheaders[y], "delegates")) { continue; }
            idx1 = dheaders[y].rfind("/") + 1;
            idx2 = dheaders[y + 1].rfind("/") + 1;
            if (dheaders[y].rfind(".") > 0) {
                n1 = dheaders[y].substr(idx1, dheaders[y].rfind(".") - idx1);
            } else {
                n1 = dheaders[y].substr(idx1);
            }
            if (dheaders[y + 1].rfind(".") > 0) {
                n2 = dheaders[y + 1].substr(idx2, dheaders[y + 1].rfind(".") - idx2);
            } else {
                n2 = dheaders[y + 1].substr(idx2);
            }
            if (omni::string::is_numeric(n1) && omni::string::is_numeric(n2)) {
                if (omni::string::util::to_type<size_t>(n1) > omni::string::util::to_type<size_t>(n2)) {
                    tmp = dheaders[y + 1];
                    dheaders[y + 1] = dheaders[y];
                    dheaders[y] = tmp;
                }
            }
        }
    }

    OmniDocuGen::DocuGen::HeaderFiles.insert(OmniDocuGen::DocuGen::HeaderFiles.begin()+iidx, dheaders.begin(), dheaders.end());

    size_t tot = OmniDocuGen::DocuGen::SourceFiles.size() + OmniDocuGen::DocuGen::HeaderFiles.size();
    up("Found {0} files: {1} source and {2} headers",
        omni::string::to_string(tot),
        omni::string::to_string(OmniDocuGen::DocuGen::SourceFiles.size()),
        omni::string::to_string(OmniDocuGen::DocuGen::HeaderFiles.size())
    );
}

/// 
/// <param name="srcdir"></param>
void OmniDocuGen::DocuGen::_ScanSourcedir(const std::string& srcdir)
{
    up(1, "Scanning directory {0}", srcdir);
    std::string ext;
    std::string exlow = omni::string::to_lower(OmniDocuGen::Program::Settings.Excluded);
    omni::seq::std_string_t vals;
    omni::io::directory::get_files(srcdir, vals);
    up(1, "Found {0} files", omni::string::to_string(vals.size()));
    omni::seq::std_string_t::iterator f;
    for (f = vals.begin(); f != vals.end(); ++f) {
        if (OmniDocuGen::Program::StopReq) { return; }
        if (OmniDocuGen::CodeGen::IsNoParse(*f) || omni::string::contains(exlow, omni::string::to_lower(*f)))
        {
            up(3, "Skipping excluded file '{0}'", *f);
            continue;
        }
        ext = omni::io::path::get_extension(*f);
        if (!OmniDocuGen::Util::IsValidExt(ext)) {
            up(3, "Skipping '{0}', invalid extension '{1}'", *f, ext);
            continue;
        }
        if (OmniDocuGen::Util::IsSourceExt(ext) || OmniDocuGen::CodeGen::IsSpecialSource(*f)) {
            OmniDocuGen::DocuGen::SourceFiles.push_back(*f);
        } else {
            OmniDocuGen::DocuGen::HeaderFiles.push_back(*f);
        }
    }
    if (OmniDocuGen::Program::StopReq) { return; }
    vals.clear();
    omni::io::directory::get_directories(srcdir, vals);
    up(1, "Found {0} subdirectories", omni::string::to_string(vals.size()));
    for (f = vals.begin(); f != vals.end(); ++f) {
        if (omni::string::contains(exlow, omni::string::to_lower(*f))) { continue; }
        OmniDocuGen::DocuGen::_ScanSourcedir(*f);
        if (OmniDocuGen::Program::StopReq) { return; }
    }
}

List<std::string> OmniDocuGen::DocuGen::GetMtiClassFilePath(MemberTypeInformation::ptr_t& mti)
{
    List<std::string> r;
    if (mti) {
        r.push_back(omni::io::path::combine(DocuGen::Classes, (mti->GetFilePath() + std::string(".html"))));
        foreach (MemberTypeInformation::ptr_t, o, mti->Overloads) {
            if (OmniDocuGen::Program::StopReq) { return r; }
            omni::sequence::add_range(r, DocuGen::GetMtiClassFilePath(*o));
        }
        foreach (MemberTypeInformation::ptr_t, m, mti->Members) {
            if (OmniDocuGen::Program::StopReq) { return r; }
            omni::sequence::add_range(r, DocuGen::GetMtiClassFilePath(*m));
        }
    }
    return r;
}

void OmniDocuGen::DocuGen::CheckClassDir()
{
    if (!omni::io::directory::exists(OmniDocuGen::DocuGen::Classes)) {
        up("Directory '{0}' does not exists, creating.", OmniDocuGen::DocuGen::Classes);
        if (OmniDocuGen::Program::Profile) {
            up(1, "Profile mode enabled, skipping creation of classes directory.");
        } else {
            omni::io::directory::create(OmniDocuGen::DocuGen::Classes);
        }
    } else {
        up("Removing old class files from {0}", OmniDocuGen::DocuGen::Classes);
        List<std::string> acd = DocuGen::GetMtiClassFilePath(OmniDocuGen::DocuGen::AllMti);
        omni::seq::std_string_t cd;
        omni::io::directory::get_files(OmniDocuGen::DocuGen::Classes, cd);
        omni_foreach (std::string, c, cd) {
            if (OmniDocuGen::Program::StopReq) { return; }
            if (c->empty() || omni::string::ends_with(*c, "index.html")) { continue; }
            if (has_not(acd, *c)) {
                up(2, "Removing stale class file: {0}", omni::string::replace(*c, (OmniDocuGen::DocuGen::Classes + std::string("/")), ""));
                Util::DeleteFile(*c);
                if (OmniDocuGen::DocuGen::DoHashZipFiles) {
                    std::string nm = omni::string::replace(*c, OmniDocuGen::DocuGen::Root, OmniDocuGen::OutPaths::TempOut);
                    up(2, "Removing old temp file {0}", nm);
                    Util::DeleteFile(nm);
                }
            }
        }
    }
}

void OmniDocuGen::DocuGen::AddTree(MemberTypeInformation::ptr_t& mti, Types::TreeNode& tv)
{
    if (!mti) { return; }
    List<Types::TreeNode>::iterator node = tv.Find(mti->FullPath, true);
    if (node != tv.Nodes.end()) {
        if (mti->IsAnOverload()) {
            std::string nm = mti->GetSignature(false, false);
            nm = nm.substr(nm.find(mti->Name));
            Types::TreeNode tn(nm);
            tn.Name = nm;
            tn.Tag = mti;
            tv.AddNode(tn);
        } else {
            foreach (MemberTypeInformation::ptr_t, m, mti->Members) {
                if (OmniDocuGen::Program::StopReq) { return; }
                Types::TreeNode tn((*m)->Name);
                tn.Name = (*m)->FullPath;
                tn.Tag = *m;
                foreach (MemberTypeInformation::ptr_t, mti2, (*m)->Members) {
                    if (OmniDocuGen::Program::StopReq) { return; }
                    DocuGen::AddTree(*mti2, tn);
                }
                foreach (MemberTypeInformation::ptr_t, mti2, (*m)->Overloads) {
                    if (OmniDocuGen::Program::StopReq) { return; }
                    DocuGen::AddTree(*mti2, tn);
                }
                node->AddNode(tn);
            }
        }
    } else {
        Types::TreeNode tn;
        if (mti->IsAnOverload()) {
            std::string nm = mti->GetSignature(false, false);
            nm = nm.substr(nm.find(mti->Name));
            tn.Text = nm;
            tn.Name = nm;
        } else {
            tn.Text = mti->Name;
            tn.Name = mti->FullPath;
        }
        tn.Tag = mti;
        foreach (MemberTypeInformation::ptr_t, mti2, mti->Members) {
            if (OmniDocuGen::Program::StopReq) { return; }
            DocuGen::AddTree(*mti2, tn);
        }
        foreach (MemberTypeInformation::ptr_t, mti2, mti->Overloads) {
            if (OmniDocuGen::Program::StopReq) { return; }
            DocuGen::AddTree(*mti2, tn);
        }
        tv.AddNode(tn);
    }
    std::sort(tv.Nodes.begin(), tv.Nodes.end());
}

bool OmniDocuGen::DocuGen::ParseNeeded()
{
    return OmniDocuGen::DocuGen::DoClasses || OmniDocuGen::DocuGen::DoClassIndex ||
            OmniDocuGen::DocuGen::DoMacroOptions || OmniDocuGen::DocuGen::DoFilesView ||
            OmniDocuGen::DocuGen::DoSyntax || OmniDocuGen::DocuGen::DoAPI || OmniDocuGen::DocuGen::DoExamples;
}

/// Links the API and Macro lists to where they're referenced at in the source
void OmniDocuGen::DocuGen::LinkMacroApiToSource()
{
    std::string code, val;
    List<std::string> sources;
    omni::sequence::add_range(sources, OmniDocuGen::DocuGen::HeaderFiles);
    omni::sequence::add_range(sources, OmniDocuGen::DocuGen::SourceFiles);

    size_t tot = 0;
    size_t tot_api = OmniDocuGen::DocuGen::SysAPIs.size();
    size_t tot_mac = OmniDocuGen::DocuGen::Macros.size();

    foreach (std::string, src, sources) {
        if (OmniDocuGen::Program::StopReq) { return; }
        code = omni::io::file::get_contents(*src);
        foreach (SysAPI, api, OmniDocuGen::DocuGen::SysAPIs) {
            if (OmniDocuGen::Program::StopReq) { return; }
            if (omni::string::contains(code, api->Name)) {
                val = omni::string::replace(*src, OmniDocuGen::Program::Settings.SourceDirectory, "");
                api->References.push_back(omni::string::replace_all(val, "\\", "/"));
                ++tot;
            }
        }
        foreach (MacroOp, op, OmniDocuGen::DocuGen::Macros) {
            if (OmniDocuGen::Program::StopReq) { return; }
            if (omni::string::contains(code, op->Name)) {
                val = omni::string::replace(*src, OmniDocuGen::Program::Settings.SourceDirectory, "");
                op->References.push_back(omni::string::replace_all(val, "\\", "/"));
                ++tot;
            }
        }
    }

    up("Totals: API's ({0}), Macros ({1}), Linked ({2})",
        omni::string::to_string(tot_api),
        omni::string::to_string(tot_mac),
        omni::string::to_string(tot)
    );
}

/// Loads the macros
/// <param name="macdir"></param>
void OmniDocuGen::DocuGen::LoadMacros(const std::string& macdir)
{
    up("Loading macro's from '{0}'", macdir);
    OmniDocuGen::DocuGen::Macros.clear();
    if (omni::io::directory::exists(macdir)) {
        omni::seq::std_string_t files;
        omni::io::directory::get_files(macdir, files);
        foreach_t (omni::seq::std_string_t, f, files) {
            OmniDocuGen::DocuGen::Macros.push_back(MacroOp(*f));
            if (OmniDocuGen::Program::StopReq) { return; }
        }
        std::sort(OmniDocuGen::DocuGen::Macros.begin(), OmniDocuGen::DocuGen::Macros.end());
        up("Loaded {0} macro's", omni::string::to_string(OmniDocuGen::DocuGen::Macros.size()));
    } else {
        up("Macro directory '{0}' not found; loading macros's failed!", macdir);
    }
}

/// Loads the system api helpers
/// <param name="apidir"></param>
void OmniDocuGen::DocuGen::LoadSystemAPI(const std::string& apidir)
{
    up("Loading system API's from '{0}'", apidir);
    OmniDocuGen::DocuGen::SysAPIs.clear();
    if (omni::io::directory::exists(apidir)) {
        omni::seq::std_string_t files;
        omni::io::directory::get_files(apidir, files);
        foreach_t (omni::seq::std_string_t, f, files) {
            OmniDocuGen::DocuGen::SysAPIs.push_back(SysAPI(*f));
            if (OmniDocuGen::Program::StopReq) { return; }
        }
        if (omni::application::args().contains("-sort")) {
            std::sort(OmniDocuGen::DocuGen::SysAPIs.begin(), OmniDocuGen::DocuGen::SysAPIs.end(), SysAPI::SortByType);
        } else {
            std::sort(OmniDocuGen::DocuGen::SysAPIs.begin(), OmniDocuGen::DocuGen::SysAPIs.end());
        }
        up("Loaded {0} system API's", omni::string::to_string(OmniDocuGen::DocuGen::SysAPIs.size()));
    } else {
        up("System API directory '{0}' not found; loading API's failed!", apidir);
    }
}

/// Scans the source directory for code files and generates HTML
/// from the source
/// <param name="srcdir"></param>
/// <param name="outdir"></param>
void OmniDocuGen::DocuGen::ScanSourceDir(const std::string& srcdir)
{
    OmniDocuGen::DocuGen::_ScanSourcedir(srcdir);
    OmniDocuGen::DocuGen::_SortSourceAndDelegateHeaders();
    OmniDocuGen::Program::SetGenerationProgress(Types::GenerationStatus::SourceScanComplete);
}

void OmniDocuGen::DocuGen::ParseSource(const Types::SourceGenType& sgt)
{
    if (!omni::io::directory::exists(OmniDocuGen::Program::Settings.SourceDirectory)) {
        throw omni::exceptions::path_exception(OmniDocuGen::Program::Settings.SourceDirectory);
    }
    if (!omni::io::directory::exists(OmniDocuGen::DocuGen::Root)) {
        OmniDocuGen::Program::AddError("Could not find outdir: " + OmniDocuGen::DocuGen::Root + "; creating...");
        if (!omni::io::directory::create(OmniDocuGen::DocuGen::Root)) {
            throw omni::exceptions::path_exception(std::string("Could not create output directory: ") + OmniDocuGen::DocuGen::Root);
        }
    }
    OmniDocuGen::Program::SetGenerationProgress(Types::GenerationStatus::ParsingFiles);
    // Scan the source
    OmniDocuGen::DocuGen::ScanSourceDir(OmniDocuGen::Program::Settings.SourceDirectory);

    // parse the macros
    OmniDocuGen::DocuGen::LoadMacros(OmniDocuGen::Program::Settings.MacroDirectory);
    OmniDocuGen::DocuGen::LoadSystemAPI(OmniDocuGen::Program::Settings.SystemAPIDirectory);
    OmniDocuGen::DocuGen::LinkMacroApiToSource();
    OmniDocuGen::Program::SetGenerationProgress(Types::GenerationStatus::MacroScanComplete);

    OmniDocuGen::DocuGen::GenerateMemberInfo((sgt == Types::SourceGenType::BuildToo));

    OmniDocuGen::DocuGen::HasParsed = true;
    // only switch tabs if we don't still have output being displayed
    OmniDocuGen::Program::SetGenerationProgress(Types::GenerationStatus::ParseComplete);
}

void OmniDocuGen::DocuGen::StartSource(const Types::SourceGenType& sgt)
{
    omni::stopwatch ssw;
    try {
        ssw.start();
        OmniDocuGen::DocuGen::ParseSource(sgt);
        ssw.stop();
        up("Source parse {0}: {1}ms ({2}s)",
            (OmniDocuGen::Program::StopReq ? "stop requested" : "thread complete"),
            omni::string::to_string(ssw.elapsed_ms()),
            omni::string::to_string(omni::math::round(static_cast<double>(ssw.elapsed_ms())/1000,3))
        );
    } catch (const std::exception& ex) {
        OmniDocuGen::Program::AddError(ex, "Error in generator thread");
    }
}
