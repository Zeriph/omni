#include "docugen.hpp"

bool OmniDocuGen::Util::DeleteFile(const std::string& fpath)
{
    if (OmniDocuGen::Program::Profile) {
        up(1, "Profile mode enabled, skipping DeleteFile('{0}'..", fpath);
        return true;
    }
    if (omni::io::file::exists(fpath)) {
        try {
            omni::io::file::remove(fpath);
            // omni::sync::sleep(50);
        } catch (const std::exception& e) { 
            OmniDocuGen::Program::AddError(e);
        }
    }
    return !omni::io::file::exists(fpath);
}

bool OmniDocuGen::Util::MoveFile(const std::string& s, const std::string& d)
{
    if (OmniDocuGen::Program::Profile) {
        up(1, "Profile mode enabled, skipping MoveFile('{0}', '{1}'..", s, d);
        return true;
    }
    if (omni::io::file::exists(s)) {
        try { omni::io::file::move(s, d); }
        catch (const std::exception& e) { OmniDocuGen::Program::AddError(e); }
    }
    return omni::io::file::exists(d);
}

bool OmniDocuGen::Util::CopyFile(const std::string& s, const std::string& d, bool o)
{
    if (OmniDocuGen::Program::Profile) {
        up(1, "Profile mode enabled, skipping CopyFile('{0}', '{1}'..", s, d);
        return true;
    }
    if (!o) {
        if (omni::io::file::exists(d)) { return true; }
    }
    if (omni::io::file::exists(s)) {
        try {
            std::string dnm = omni::io::path::get_parent_name(d);
            if (!omni::io::directory::exists(dnm)) { omni::io::directory::create(dnm); }
            omni::io::file::copy(s, d, o);
        } catch (const std::exception& ex) { OmniDocuGen::Program::AddError(ex); }
    }
    return omni::io::file::exists(d);
}

void OmniDocuGen::Util::CopyDirectory(const std::string& s, const std::string& sp, const std::string& d, bool r, bool o)
{
    if (OmniDocuGen::Program::Profile) {
        up(1, "Profile mode enabled, skipping CopyDirectory('{0}', '{1}', '{2}'..", s, sp, d);
        return;
    }
    if (r) {
        omni::seq::std_string_t dirs;
        omni::io::directory::get_directories(s, dirs);
        foreach_t (omni::seq::std_string_t, subd, dirs) {
            if (OmniDocuGen::Program::StopReq) { return; }
            OmniDocuGen::Util::CopyDirectory(*subd, sp, d, r, o);
        }
    }
    omni::seq::std_string_t files;
    omni::io::directory::get_files(s, files);
    foreach_t (omni::seq::std_string_t, f, files) {
        if (OmniDocuGen::Program::StopReq) { return; }
        OmniDocuGen::Util::CopyFile(*f, omni::string::replace(*f, sp, d), o);
    }
}

void OmniDocuGen::Util::CopyDirectory(const std::string& s, const std::string& d, bool r, bool o)
{
    OmniDocuGen::Util::CopyDirectory(s, omni::string::trim_end(s, OMNI_PATH_SEPARATOR), d, r, o);
}

void OmniDocuGen::Util::CopyDirectory(const std::string& s, const std::string& d, bool r)
{
    OmniDocuGen::Util::CopyDirectory(s, d, r, false);
}

bool OmniDocuGen::Util::WriteFile(const std::string& file, std::string text, int rtry, int tout, bool repnl)
{
    if (OmniDocuGen::Program::Profile) {
        up(1, "Profile mode enabled, skipping WriteFile('{0}'..", file);
        return true;
    }
    std::string d = omni::io::path::get_parent_name(file);
    if (!omni::io::directory::exists(d)) {
        omni::io::directory::create(d);
    }
    for (int i = 0; i < rtry; ++i) {
        try {
            if (!omni::io::file::exists(file)) {
                omni::io::file::create(file);
            }
            omni::io::file::set_size(file, 0);
            if (repnl) {
                omni::io::file::write(file, omni::string::replace_all(text, "\r\n", "\n"));
            } else {
                omni::io::file::write(file, text);
            }
            if (tout > 0) { omni::sync::sleep(tout); }
            break;
        } catch (const std::exception& ex) {
            OmniDocuGen::Program::AddError(ex, std::string("file: ") + file);
            omni::sync::sleep((tout * (i + 1)));
        }
    }
    return omni::io::file::exists(file);
}

bool OmniDocuGen::Util::WriteFile(std::string file, std::string text)
{
    return OmniDocuGen::Util::WriteFile(file, text, 5, 0, true);
}

bool OmniDocuGen::Util::WriteFile(std::string file, std::string text, bool repnl)
{
    return OmniDocuGen::Util::WriteFile(file, text, 5, 0, repnl);
}

void OmniDocuGen::Util::WriteRedirect(const std::string& dir, const std::string& redir, uint32_t idx)
{
    std::string lnk = "<html><head><meta HTTP-EQUIV=\"REFRESH\" content=\"0; url=";
    for (uint i = 0; i < idx; ++i) { lnk += "../"; }
    lnk += (redir + "\"></head></html>");
    OmniDocuGen::Util::WriteFile(omni::io::path::combine(dir, "index.html"), lnk);
}

void OmniDocuGen::Util::CheckAndCreateDirWithRedir(const std::string& dir, const std::string& redir, uint32_t idx)
{
    if (omni::io::directory::exists(dir)) {
        try {
            if (OmniDocuGen::Program::Profile) {
                up(1, "Profile mode enabled, skipping delete dir ('{0}'..", dir);
            } else {
                omni::io::directory::remove(dir, true);
            }
        } catch (const std::exception& ex) {
            OmniDocuGen::Program::AddError(ex);
        }
    }
    if (!omni::io::directory::exists(dir)) {
        try {
            if (OmniDocuGen::Program::Profile) {
                up(1, "Profile mode enabled, skipping create dir ('{0}'..", dir);
            } else {
                omni::io::directory::create(dir);
            }
        } catch (const std::exception& ex) {
            OmniDocuGen::Program::AddError(ex);
        }
    }
    if (!redir.empty()) { OmniDocuGen::Util::WriteRedirect(dir, redir, idx); }
}

void OmniDocuGen::Util::CheckAndCreateDir(const std::string& dir)
{
    OmniDocuGen::Util::CheckAndCreateDirWithRedir(dir, "", 0);
}

void OmniDocuGen::Util::WriteRedirectDirectories(const std::string& dir, const std::string& redir, uint32_t idx)
{
    OmniDocuGen::Util::WriteRedirect(dir, redir, idx);
    omni::seq::std_string_t dirs;
    omni::io::directory::get_directories(dir, dirs);
    omni_foreach (std::string, sdir, dirs) {
        if (OmniDocuGen::Program::StopReq) { return; }
        OmniDocuGen::Util::WriteRedirectDirectories(*sdir, redir, (idx + 1));
    }
}

bool OmniDocuGen::Util::ZipDirectory(const std::string& dir, const std::string& z, bool no_html)
{
    if (OmniDocuGen::Program::Profile) {
        up(1, "Profile mode enabled, skipping zip dir ('{0}'..", dir);
        return true;
    }
    bool id = true; // TODO: what the hell was this for?
    std::string zip;
    
    omni_sequence_t<std::string> zpaths = omni::cstring::split(OmniDocuGen::Program::Settings.PathsFor7z, ",");
    omni_foreach(std::string, z, zpaths) {
        if (OmniDocuGen::Program::StopReq) { return false; }
        if (omni::io::file::exists(*z)) {
            zip = *z;
            break;
        }
    }
    if (zip.empty() || !omni::io::file::exists(zip)) {
        up("Could not find 7zip on this system.");
        return false;
    }
    if (system(NULL) == 0) {
        up("The 'system' command is not available on this system, cannot zip.");
        return false;
    }
    try {
        std::string args, cmd;
        int rv = 0;
        cmd = "chmod -R 777 '" + dir + "'";
        up(2, "Executing zip command '{0}'", cmd);

        if ((rv = system(cmd.c_str())) != 0) {
            up("Return value for command returned non zero value: {0}", omni::string::to_string(rv));
        }
        if (id) {
            if (no_html) {
                args = Util::Format("a -tzip \"{0}\" \"{1}\" -x!*.html", z, dir);
            } else {
                args = Util::Format("a -tzip \"{0}\" \"{1}\"", z, dir);
            }
            cmd = zip + " " + args;
            if (Program::Verbosity < 1) { cmd += " > /dev/null"; }
            up(2, "Executing zip command '{0}'", cmd);
            if ((rv = system(cmd.c_str())) != 0) {
                up("Return value for command returned non zero value: {0}", omni::string::to_string(rv));
            }
        } else {
            omni::seq::std_string_t dirs, files;
            omni::io::directory::get_directories(dir, dirs);
            omni::io::directory::get_files(dir, files);
            omni::seq::std_string_t ex_list = omni::string::split(omni::string::to_lower(Program::Settings.Excluded), ",");
            bool is_ex = false;
            omni_foreach (std::string, d, dirs) {
                if (OmniDocuGen::Program::StopReq) { return false; }
                is_ex = false;
                omni_foreach(std::string, ex, ex_list) {
                    if (omni::string::contains(omni::string::to_lower(*d), *ex)) {
                        is_ex = true;
                        break;
                    }
                }
                if (is_ex) { continue; }
                args = Util::Format("a -tzip \"{0}\" \"{1}\"", z, *d);
                cmd = zip + " " + args;
                if (Program::Verbosity < 2) { cmd += " > /dev/null"; }
                up(2, "Executing zip command '{0}'", cmd);
                if ((rv = system(cmd.c_str())) != 0) {
                    up("Return value for command returned non zero value: {0}", omni::string::to_string(rv));
                }
            }
            omni_foreach (std::string, f, files) {
                if (OmniDocuGen::Program::StopReq) { return false; }
                is_ex = false;
                omni_foreach(std::string, ex, ex_list) {
                    if (omni::string::contains(omni::string::to_lower(*f), *ex)) {
                        is_ex = true;
                        break;
                    }
                }
                if (is_ex) { continue; }
                args = Util::Format("a -tzip \"{0}\" \"{1}\"", z, *f);
                cmd = zip + " " + args;
                if (Program::Verbosity < 2) { cmd += " > /dev/null"; }
                up(2, "Executing zip command '{0}'", cmd);
                if ((rv = system(cmd.c_str())) != 0) {
                    up("Return value for command returned non zero value: {0}", omni::string::to_string(rv));
                }
            }
        }
    } catch (const std::exception& ex) {
        Program::AddError(ex, Util::Format("Error zipping directory {0}", dir));
        return false;
    }
    return true;
}

bool OmniDocuGen::Util::ZipDirectory(const std::string& dir, const std::string& z)
{
    return OmniDocuGen::Util::ZipDirectory(dir, z, false);
}

bool OmniDocuGen::Util::RemoveEntryFromZip(const std::string& z, const std::string& f)
{
    if (OmniDocuGen::Program::Profile) {
        up(1, "Profile mode enabled, skipping remove entry from zip ('{0}', '{1}'..", z, f);
        return true;
    }
    std::string zip;
    omni_sequence_t<std::string> zpaths = omni::cstring::split(OmniDocuGen::Program::Settings.PathsFor7z, ",");
    omni_foreach(std::string, z, zpaths) {
        if (OmniDocuGen::Program::StopReq) { return false; }
        if (omni::io::file::exists(*z)) {
            zip = *z;
            break;
        }
    }
    if (zip.empty() || !omni::io::file::exists(zip)) {
        up("Could not find 7zip on this system.");
        return false;
    }
    if (system(NULL) == 0) {
        up("The 'system' command is not available on this system, cannot zip.");
        return false;
    }
    // d (Delete) command - Deletes files from archive.
    // Example: '7z d archive.zip *.bak -r'
    // -deletes *.bak files from archive archive.zip recursively.
    try {
        int rv = 0;
        std::string args = Util::Format("d \"{0}\" \"{1}\"{2}", z, f, ((omni::string::ends_with(f, "/") || omni::string::ends_with(f, "\\")) ? " -r" : ""));
        std::string cmd = zip + " " + args;
        if (Program::Verbosity < 2) { cmd += " > /dev/null"; }
        up(3, "Executing zip command '{0}'", cmd);
        if ((rv = system(cmd.c_str())) != 0) {
            up("Return value for command returned non zero value: {0}", omni::string::to_string(rv));
        }
    } catch (const std::exception& ex) {
        Program::AddError(ex, Util::Format("Error removing {0} from archive {1}", f, z));
        return false;
    }
    return true;
}

std::string OmniDocuGen::Util::LastWriteTime(const std::string& file)
{
    if (omni::io::file::exists(file)) {
        struct stat attr;
        char date[255] = {0};
        std::string tmp, utc;
        int iutc;
        memset(date, 0, sizeof(date));
        stat(file.c_str(), &attr);
        strftime(date, 255, "%z", localtime(&(attr.st_ctime)));
        tmp = std::string(date);
        memset(date, 0, sizeof(date));
        if (!omni::char_util::is_digit(tmp[0])) {
            utc = tmp.substr(0, 1);
            tmp = tmp.substr(1);
        }
        if (omni::string::is_numeric(tmp)) {
            iutc = omni::string::util::to_type<int>(tmp);
            iutc /= 100;
            if (iutc < 10) {
                utc += "0" + omni::string::to_string(iutc);
            } else {
                utc += omni::string::to_string(iutc);
            }
        }
        strftime(date, 255, "%Z", localtime(&(attr.st_ctime)));
        tmp = std::string(date);
        memset(date, 0, sizeof(date));
        utc = " (" + utc + " " + tmp + ")";
        strftime(date, 255, "%m/%d/%Y %H:%M:%S", localtime(&(attr.st_ctime)));
        return std::string(date) + utc;
    }
    return "00/00/0000 00:00:00 (+0 UTC)";
}

std::string OmniDocuGen::Util::NormalizeEndings(const std::string& s)
{
    std::string r = omni::string::replace_all(s, "\r\n", "\n");
    return omni::string::replace_all(r, "\n", "\r\n");
}

std::string OmniDocuGen::Util::NormalizeEndings(const std::string& s, bool usrn)
{
    std::string r = (!usrn ? s : omni::string::replace_all(s, "\r\n", "\n"));
    return omni::string::replace_all(r, "\n", "\r\n");
}

std::string OmniDocuGen::Util::NormalizeRN(const std::string& s)
{
    return omni::string::replace_all(s, "\n", "\r\n");
}

std::string OmniDocuGen::Util::NormalizeN(const std::string& s)
{
    return omni::string::replace_all(s, "\r\n", "\n");
}

std::string OmniDocuGen::Util::ToHTML(const std::string& s)
{
    std::string ret = omni::string::replace_all(s, "&", "&amp;");
    ret = omni::string::replace_all(ret, "<", "&lt;");
    ret = omni::string::replace_all(ret, ">", "&gt;");
    ret = omni::string::replace_all(ret, "\"", "&quot;");
    ret = omni::string::replace_all(ret, "'", "&#39;");
    ret = omni::string::replace_all(ret, "&amp;amp;", "&amp;");
    ret = omni::string::replace_all(ret, "&amp;lt;", "&lt;");
    ret = omni::string::replace_all(ret, "&amp;gt;", "&gt;");
    ret = omni::string::replace_all(ret, "&amp;quot;", "&quot;");
    ret = omni::string::replace_all(ret, "&amp;#39;", "&#39;");
    return ret;
    // return System.Web.HttpUtility.HtmlEncode(s);
}

std::string OmniDocuGen::Util::TabToWhitespaceHTML(const std::string& s)
{
    std::string r = s;
    r = omni::string::replace_all(r, "    ", "\t");
    r = omni::string::replace_all(r, "\t", "&nbsp;&nbsp;&nbsp;&nbsp;");
    return r;
}

std::string OmniDocuGen::Util::StripHTMLbr(const std::string& s)
{
    std::string r = s;
    r = omni::string::replace_all(r, "<br />", "");
    r = omni::string::replace_all(r, "<br>", "");
    return r;
}

List<std::string> OmniDocuGen::Util::SplitAtEndings(const std::string& s)
{
    //return s.Split(OMNI_EOL_RN, std::stringSplitOptions.None);
    return omni::string::split< List >(s, "\r\n", std::size_t(0));
}

List<std::string> OmniDocuGen::Util::Split(const std::string& s, const std::string& del)
{
    //return s.Split(OMNI_EOL_RN, std::stringSplitOptions.None);
    return omni::string::split< List >(s, del, std::size_t(0));
}

int OmniDocuGen::Util::IndexOfNonWsChar(const std::string& s)
{
    for (int i = 0; i < s.length(); ++i) {
        if (!omni::char_util::is_white_space(s[i])) { return i; }
    }
    return -1;
}

int OmniDocuGen::Util::IndexOfWsChar(const std::string& s)
{
    for (int i = 0; i < s.length(); i++) {
        if (omni::char_util::is_white_space(s[i])) { return i; }
        //if (s[i] == '\r' || s[i] == '\n') { return i; }
    }
    return -1;
}

int OmniDocuGen::Util::IndexOfNonWsChar(const std::string& s, int idx)
{
    for (; idx < s.length(); ++idx) {
        if (!omni::char_util::is_white_space(s[idx])) { return idx; }
    }
    return -1;
}

int OmniDocuGen::Util::IndexOfWsChar(const std::string& s, int idx)
{
    for (; idx < s.length(); ++idx) {
        if (omni::char_util::is_white_space(s[idx])) { return idx; }
        //if (s[idx] == '\r' || s[idx] == '\n') { return idx; }
    }
    return -1;
}

std::string OmniDocuGen::Util::ReplaceBeginingWhitespaceHTML(const std::string& s)
{
    int nws = OmniDocuGen::Util::IndexOfNonWsChar(s);
    if (nws < 0) { return s; }
    std::string r = omni::string::trim_front(s, std::string("\t "));// s.TrimStart('\t', ' ');
    for (int i = 0; i < nws; ++i) {
        r = "&nbsp;" + r;
    }
    return r;
}

std::string OmniDocuGen::Util::DiskSpaceToString(long diskSpace, int digits, std::string btype)
{
    std::string s = omni::string::to_string(diskSpace);
    if (btype == "") {
        btype = "B";
        if (diskSpace > OmniDocuGen::Util::GiB) { btype = "GB"; }
        else if (diskSpace > OmniDocuGen::Util::MiB) { btype = "MB"; }
        else if (diskSpace > OmniDocuGen::Util::KiB) { btype = "KB"; }
    }
    if (btype == "KB") {
        s =  omni::string::to_string(omni::math::round(((double)diskSpace / (double)OmniDocuGen::Util::KiB), digits));
    } else if (btype == "MB") {
        s =  omni::string::to_string(omni::math::round(((double)diskSpace / (double)OmniDocuGen::Util::MiB), digits));
    } else if (btype == "GB") {
        s =  omni::string::to_string(omni::math::round(((double)diskSpace / (double)OmniDocuGen::Util::GiB), digits));
    }
    return s + std::string(" ") + btype; // std::string.Format("{0} {1}", s, btype);
}

std::string OmniDocuGen::Util::DiskSpaceToString(long diskSpace)
{
    return OmniDocuGen::Util::DiskSpaceToString(diskSpace, 3, "");
}

std::string OmniDocuGen::Util::MergeWithNewLine(const List<std::string>& arr)
{
    std::string r = "";
    foreach_c (std::string, itr, arr) {
        r += *itr + std::string("\r\n");
    }
    return r;
}

List<int32_t> OmniDocuGen::Util::IndexesOf(const std::string& s, const std::string& val)
{
    List<int32_t> r;
    std::string t = s;
    size_t x = 0;
    size_t i = t.find(val);
    while (i != std::string::npos) {
        r.push_back(i);
        i += val.length();
        if (i >= s.length()) { break; }
        t = s.substr(i);
        x = t.find(val);
        i = ((x == std::string::npos) ? x : (i + x));
    }
    return r;
}

std::map<size_t, size_t> OmniDocuGen::Util::IndexOfCompliments(const std::string& str, const std::string& val, bool useFindFirst)
{
    std::map<size_t, size_t> ret;
    size_t i1, i2;
    if (useFindFirst) {
        size_t x, y;
        x = str.find_first_of(val);
        while (x != std::string::npos) {
            y = str.find_first_not_of(val, x);
            ret[x] = y;
            x = str.find_first_of(val, y+1);
        }
    } else {
        List<int32_t> vals = Util::IndexesOf(str, val);
        foreach (int32_t, idx, vals) {
            if (OmniDocuGen::Program::StopReq) { return ret; }
            i1 = *idx;
            if (++idx != vals.end()) {
                i2 = *idx;
            } else {
                i2 = std::string::npos;
            }
            ret[i1] = i2;
            if (idx == vals.end()) { break; }
        }
    }
    return ret;
}

std::map<size_t, size_t> OmniDocuGen::Util::IndexOfCompliments(const std::string& str, const std::string& val)
{
    return OmniDocuGen::Util::IndexOfCompliments(str, val, true);
}

// does auto '{' '}'
int32_t OmniDocuGen::Util::IndexOfCompliment(const std::string& s, int32_t idx)
{
    int32_t lvl = 0;
    for (; idx < s.length(); ++idx) {
        if (s[idx] == '{') { ++lvl; }
        if (s[idx] == '}') { --lvl; }
        if (lvl <= 0) { break; }
    }
    if (lvl > 0) { idx = -1; }
    return idx;
}

int32_t OmniDocuGen::Util::IndexOfCompliment(const std::string& s, int32_t idx, char bc, char ec)
{
    int32_t lvl = 0;
    for (; idx < s.length(); ++idx) {
        if (s[idx] == bc) { ++lvl; }
        if (s[idx] == ec) { --lvl; }
        if (lvl <= 0) { break; }
    }
    if (lvl > 0) { idx = -1; }
    return idx;
}

int32_t OmniDocuGen::Util::IndexOfCompliment(const std::string& s, int32_t idx, const std::string& bc, const std::string& ec)
{
    if (idx < 0) { return idx; }
    int32_t lvl = 0;
    bool inc = false;
    for (; idx < s.length(); ++idx) {
        if (s.substr(idx, bc.length()) == bc) {
            ++lvl;
            idx += bc.length();
            inc = true;
        }
        if (idx + ec.length() < s.length()) {
            if (s.substr(idx, ec.length()) == ec) {
                --lvl;
                if (lvl > 0) { idx += ec.length(); }
                inc = true;
            }
        } else {
            idx = s.length();
            --lvl;
        }
        if (lvl <= 0) { break; }
        if (inc) { --idx; inc = false;  }
    }
    if (lvl > 0) { idx = -1; }
    return idx;
}

int32_t OmniDocuGen::Util::IndexOfChar(const std::string& s, int32_t idx, char c)
{
    for (; idx < s.length(); ++idx) {
        if (s[idx] == c) { return idx; }
    }
    return -1;
}

int32_t OmniDocuGen::Util::IndexOfString(const std::string& s, int32_t idx, const std::string& t)
{
    if (t.empty()) { return -1; }
    char c = t[0]; int32_t v = -1;
    std::string x = "";
    for (; idx < s.length(); ++idx) {
        if (s[idx] == c) {
            v = idx;
            x = s[idx];
            for (++idx; idx < s.length(); ++idx) {
                x += s[idx];
                if (x.length() == t.length()) {
                    if (x == t) { return v; }
                    x = "";
                    idx = v;
                    break;
                }
            }
        }
    }
    return -1;
}

int32_t OmniDocuGen::Util::IndexOfStringReverse(const std::string& s, int32_t idx, const std::string& t)
{
    if (t.empty()) { return -1; }
    char c = t[0]; int32_t v = -1;
    std::string x = "";
    for (; idx >= 0; --idx) {
        if (s[idx] == c) {
            v = idx;
            x = s[idx];
            for (--idx; idx >= 0; --idx) {
                x += s[idx];
                if (x.length() == t.length()) {
                    if (x == t) { return v; }
                    x = "";
                    idx = v;
                    break;
                }
            }
        }
    }
    return -1;
}

int32_t OmniDocuGen::Util::TemplateBefore(const std::string& s, int32_t clsidx)
{
    for (clsidx -= 1; clsidx >= 0; --clsidx) {
        if (!omni::char_util::is_white_space(s[clsidx])) {
            if (s[clsidx] == '>') {
                std::string f = ">";
                for (clsidx -= 1; clsidx >= 0; --clsidx) {
                    f = s[clsidx] + f;
                    if (omni::string::starts_with(f, "template <")) {
                        return clsidx;
                    }
                }
            }
            break;
        }
    }
    return -1;
}

int32_t OmniDocuGen::Util::CommentBefore(const std::string& s, int32_t idx)
{
    size_t pos = s.rfind("*/", idx);
    if (pos != std::string::npos) {
        // found the '*/', now search for the '/**'
        pos = s.rfind("/**", pos);
        if (pos != std::string::npos) {
            return pos;
        }
    }
    return -1;
}

std::string OmniDocuGen::Util::GetComment(const std::string& s, int32_t idx)
{
    size_t ti = ((idx > 0) ? idx : s.find("/**"));
    if (ti != std::string::npos) {
        std::string c = s.substr(ti);
        return c.substr(0, c.find("*/") + 2);
    }
    return "";
}

std::string OmniDocuGen::Util::GetComment(const std::string& s)
{
    return GetComment(s, 0);
}

bool OmniDocuGen::Util::IsWithinComment(const std::string& s, const std::string& val)
{
    if (omni::string::contains(s, "//") || omni::string::contains(s, "/*")) {
        size_t i = s.find(val);
        std::string t1 = s.substr(0, i);
        std::string t2 = s.substr(i);
        i = t1.rfind("\n");
        t1 = ((i != std::string::npos) ? t1.substr(i) : t1);
        i = t2.find("\n");
        t2 = ((i != std::string::npos) ? t2.substr(0, i) : t2);
        std::string c = omni::string::trim_front(t1) + omni::string::trim_end(t2);
        if (omni::string::contains(c, "//") || omni::string::contains(c, "/*") || omni::string::contains(c, "*/")) {
            return true;
        }
    }
    return false;
}

std::string OmniDocuGen::Util::ReplaceAll(std::string hay, const std::string& ndl, const std::string& rep)
{
    if (hay.empty()) { return hay; }
    typedef std::map<size_t, size_t> idx_map;
    char b, a;
    bool do_it, find_it;
    //idx_map qts;
    size_t s, e, l, np;
    std::string line, qt;
    size_t nsz = ndl.size();
    size_t spos = hay.find(ndl);
    while (spos != std::string::npos) {
        // is the begin char in a word?
        a = '\0'; b = '\0';
        do_it = false; find_it = false;
        if (spos > 0) {
            b = hay[spos-1];
            do_it = omni::char_util::is_alpha_num(b);
        }
        // is the end char in a word?
        if (!do_it && ((spos + nsz) < hay.size())) {
            a = hay[spos+nsz];
            do_it = omni::char_util::is_alpha_num(a);
        }
        // is the end/begin something like this->send or this.send or do_send or send_it or the such, etc?
        if (!do_it) {
            // ????? b == '*' || b == '&' || b == '@' ||
            if (b == '#' || b == '_' || a == '_' || b == '.' || a == '.') {
                do_it = true;
            } else {
                if (((spos > 2) && (hay.substr((spos-2), 2) == "->")) ||
                    (((spos + nsz + 3) < hay.size()) && (hay.substr((spos+nsz), 2) == "->")))
                {
                    do_it = true;
                }
            }
        }
        // in a C99 comment /* here's an example */
        if (!do_it) {
            s = hay.rfind("/*", spos);
            if (s != std::string::npos) {
                // A /* C99 comment */ was found, so look for the
                // begining and end of the comment and see if the
                // value is in there
                e = hay.find("*/", s);
                if (e == std::string::npos) { e = hay.size(); }
                if ((s < spos) && (e > spos)) {
                    //it's in a /* C99 comment */, so remove it
                    do_it = true;
                }
            }
        }
        // in a single line comment // here's an example
        if (!do_it) {
            // now look for it in a single line [//] comment
            s = hay.rfind("//", l);
            if (s != std::string::npos) {
                // A [//] single line comment was found, so look for the
                // end of the line and see if the value is in there
                e = hay.find("\n", s);
                if (e == std::string::npos) { e = hay.size(); }
                if ((s < spos) && (e > spos)) {
                    // it's in a single line comment, so remove it
                    do_it = true;
                }
            }
        }
        // now look for it in between double quotes (i.e. strings), ["here's an example"]
        if (!do_it) {
            s = hay.rfind("\n", spos);
            if (s == std::string::npos) { s = 0; }
            e = hay.find("\n", spos);
            if (e == std::string::npos) { e = hay.size(); }
            line = hay.substr(s, (e - s));
            if (omni::string::contains(line, "&quot;")) {
                l = spos - s;
                np = line.find(ndl, l);
                qt = "&quot;";
                s = line.find(qt);
                while (s != std::string::npos) {
                    e = line.find(qt, s+1);
                    if (e != std::string::npos) {
                        if (line[e-1] == '\\' && line[e-2] != '\\') { // != "\\"
                            e = line.find(qt, e+1);
                            if (e == std::string::npos) {
                                e = line.size();
                            }
                        }
                        if ((s < np) && (e > np)) {
                            do_it = true;
                            break;
                        }
                        if (e == line.size()) {
                            break;
                        } else {
                            s = line.find(qt, e + 1);
                        }
                    } else {
                        break;
                    }
                }
            }
        }
        if (do_it) {
            // the word we are looking for is 'within' a word, function name, quotes, or comment, so don't replace it
            spos = hay.find(ndl, (spos+nsz));
            continue;
        }
        hay.replace(spos, nsz, rep);
        spos = hay.find(ndl, spos + rep.size());
    }
    return hay;
}

std::string OmniDocuGen::Util::StripDocCommentStars(const std::string& s)
{
    size_t pos;
    std::string r, x;
    List<std::string> tmps = OmniDocuGen::Util::SplitAtEndings(s);
    foreach (std::string, itr, tmps) {
        x = omni::string::trim(*itr);
        if (x.length() > 2 && x.substr(0, 3) == "/**") { x = x.substr(3); }
        else if (x.length() > 1 && x.substr(0, 2) == "*/") { x = x.substr(2); }
        if (omni::string::contains(x, "*/")) {
            x = x.substr(0, x.rfind("*/"));
        }
        x = omni::string::trim(x);
        x = omni::string::trim_end(x, "*");
        x = omni::string::trim_front(x, "*");
        r += omni::string::trim(x) + "\r\n";
    }
    return omni::string::trim_end(r);
}

std::string OmniDocuGen::Util::StripComments(const std::string& s)
{
    if (s.empty()) { return s; }
    try {
        if (omni::string::contains(s, "//") || omni::string::contains(s, "/*")) {
            std::string r = "", x = "";
            List<std::string> tmps = OmniDocuGen::Util::SplitAtEndings(s);
            for (int32_t i = 0; i < tmps.size(); ++i) {
                x = tmps[i];
                if (omni::string::contains(x, "//")) {
                    int32_t y = (x.find("//") - 1);
                    if (y < 0) { y = 0; }
                    x = x.substr(0, y);
                }
                if (omni::string::contains(x, "/*")) {
                    if (omni::string::contains(x, "*/")) {
                        int32_t y = x.find("/*");
                        int32_t z = x.find("*/", y); // OmniDocuGen::Util::IndexOfString(x, y, "*/");
                        std::string t = x.substr(y, ((z >= 0 ? z : x.length()) - y) + 2);
                        x = omni::string::replace(x, t, "");
                    } else {
                        for (++i; i < tmps.size(); ++i) {
                            x = tmps[i];
                            if (omni::string::contains(x, "*/")) {
                                int32_t z = x.find("*/", 0) + 2; // OmniDocuGen::Util::IndexOfString(x, 0, "*/") + 2;
                                if (z >= x.length()) {
                                    x = "";
                                } else {
                                    x = x.substr(z);
                                }
                                break;
                            }
                        }
                    }
                }
                r += x + "\r\n";
            }
            return r;
        }
    } catch (const std::exception& ex) {
        OmniDocuGen::Program::AddError(ex, "couldn't strip comments");
    }
    return s;
}

std::string OmniDocuGen::Util::StripComment(const std::string& code)
{
    std::string ret = code;
    int32_t idx = ret.find("/**"); int32_t idx2 = -1;
    std::string t1; std::string t2;
    while (idx >= 0) {
        idx2 = ret.find("*/", idx) + 2;
        t1 = ret.substr(0, idx);
        t2 = omni::string::trim_front(ret.substr(idx2), " \r\n");
        ret = t1 + t2;
        idx = ret.find("/**");
    }
    return ret;
}

std::string OmniDocuGen::Util::ToFilePath(const std::string& s)
{
    if (s.empty()) { return s; }
    std::string r = omni::string::to_lower(s);
    std_foreach_c (path_map, it, OmniDocuGen::Util::m_validPaths) {
        if (OmniDocuGen::Program::StopReq) { return ""; }
        // it->first == key, it->second == value
        r = omni::string::replace_all(r, it->first, it->second);
    }
    //r = (omni::string::contains(r, "_") ? r.Replace("_", "@5F") : r).Replace("::", "_");
    /*for (it = OmniDocuGen::Util::m_validPaths.begin(); it != OmniDocuGen::Util::m_validPaths.end(); ++it) {
        // it->first == key, it->second == value
        if (omni::string::contains(r, it->first)) {
            r = omni::string::replace_all(r, it->first, it->second);
        }
    }*/
    return r;
}

std::string OmniDocuGen::Util::GetTag(const std::string& s, const std::string& tag_name)
{
    std::string ot = std::string("<") + tag_name + std::string(">");
    std::string ct = std::string("</") + tag_name + std::string(">");
    int32_t idx = s.find(ot);
    if (idx >= 0) { // contains opening tag
        int32_t edx = OmniDocuGen::Util::IndexOfCompliment(s, idx, ot, ct);
        if (edx > 0) {
            int32_t len = (edx + ct.length()) - idx;
            if (len < 0) {
                return s.substr(idx);
            } else  if ((s.length() < len) || (s.length() < (idx + len))) {
                return s.substr(idx);
            }
            return s.substr(idx, len);
        }
    }
    return std::string();
}

std::string OmniDocuGen::Util::GetTagData(const std::string& s, const std::string& tag_name)
{
    std::string tag = OmniDocuGen::Util::GetTag(s, tag_name);
    if (!tag.empty()) {
        std::string ot = std::string("<") + tag_name + std::string(">");
        std::string ct = std::string("</") + tag_name + std::string(">");
        return tag.substr(ot.length(), tag.length() - ot.length() - ct.length());
    }
    return std::string();
}

std::string OmniDocuGen::Util::RemoveTag(const std::string& s, const std::string& tag_name)
{
    std::string ot = std::string("<") + tag_name + std::string(">");
    std::string ct = std::string("</") + tag_name + std::string(">");
    int32_t idx = s.find(ot);
    if (idx >= 0) { // contains opening tag
        int32_t edx = OmniDocuGen::Util::IndexOfCompliment(s, idx, ot, ct);
        if (edx > 0) {
            edx += ct.length();
            return s.substr(0, idx) + s.substr(edx);
        }
    }
    return s;
}

std::string OmniDocuGen::Util::GetLineOfStringData(const std::string& str, const std::string& find, size_t start)
{
    size_t pos = str.find(find, start);
    if (pos != std::string::npos) {
        std::string ret = str;
        pos = ret.find("\n", pos);
        if (pos != std::string::npos) {
            ret = ret.substr(0, pos);
            if (ret.substr(ret.size()-1) == "\r") {
                ret = ret.substr(0, ret.size()-1);
            }
        }
        pos = ret.rfind("\n");
        if (pos != std::string::npos) {
            return ret.substr(pos+1);
        }
        return ret;
    }
    return str;

}

std::string OmniDocuGen::Util::GetLineOfStringData(const std::string& str, const std::string& find)
{
    return GetLineOfStringData(str, find, 0);
}

bool OmniDocuGen::Util::IsPrivate(const OmniDocuGen::Types::CodeScopeAcessType& csat)
{
    return csat == OmniDocuGen::Types::CodeScopeAcessType::Private;
}

bool OmniDocuGen::Util::IsProtected(const OmniDocuGen::Types::CodeScopeAcessType& csat)
{
    return csat == OmniDocuGen::Types::CodeScopeAcessType::Protected;
}

bool OmniDocuGen::Util::IsPublic(const OmniDocuGen::Types::CodeScopeAcessType& csat)
{
    return csat == OmniDocuGen::Types::CodeScopeAcessType::Public;
}

bool OmniDocuGen::Util::IsNamespace(const OmniDocuGen::Types::CodeStructureType&  cst)
{
    return (cst == OmniDocuGen::Types::CodeStructureType::Namespace);
}

bool OmniDocuGen::Util::IsFile(const OmniDocuGen::Types::CodeStructureType&  cst)
{
    return (cst == OmniDocuGen::Types::CodeStructureType::File);
}

bool OmniDocuGen::Util::IsEnum(const OmniDocuGen::Types::CodeStructureType&  cst)
{
    return (cst == OmniDocuGen::Types::CodeStructureType::Enum);
}

bool OmniDocuGen::Util::IsStruct(const OmniDocuGen::Types::CodeStructureType&  cst)
{
    return (cst == OmniDocuGen::Types::CodeStructureType::Struct);
}

bool OmniDocuGen::Util::IsClass(const OmniDocuGen::Types::CodeStructureType&  cst)
{
    return (cst == OmniDocuGen::Types::CodeStructureType::Class);
}

bool OmniDocuGen::Util::IsCtor(const OmniDocuGen::Types::CodeStructureType&  cst)
{
    return (cst == OmniDocuGen::Types::CodeStructureType::Ctor);
}

bool OmniDocuGen::Util::IsDtor(const OmniDocuGen::Types::CodeStructureType&  cst)
{
    return (cst == OmniDocuGen::Types::CodeStructureType::Dtor);
}

bool OmniDocuGen::Util::IsFunction(const OmniDocuGen::Types::CodeStructureType&  cst)
{
    return (cst == OmniDocuGen::Types::CodeStructureType::Function ||
            cst == OmniDocuGen::Types::CodeStructureType::Operator ||
            cst == OmniDocuGen::Types::CodeStructureType::Ctor ||
            cst == OmniDocuGen::Types::CodeStructureType::Dtor);
}

bool OmniDocuGen::Util::IsMember(const OmniDocuGen::Types::CodeStructureType&  cst)
{
    return (cst == OmniDocuGen::Types::CodeStructureType::Member);
}

bool OmniDocuGen::Util::IsTypedef(const OmniDocuGen::Types::CodeStructureType&  cst)
{
    return (cst == OmniDocuGen::Types::CodeStructureType::Typedef);
}

bool OmniDocuGen::Util::IsNsOrClass(const OmniDocuGen::Types::CodeStructureType&  cst)
{
    return (cst == OmniDocuGen::Types::CodeStructureType::Namespace ||
            cst == OmniDocuGen::Types::CodeStructureType::Class);
}

bool OmniDocuGen::Util::IsMemberFnType(const OmniDocuGen::Types::CodeStructureType&  cst)
{
    return (cst == OmniDocuGen::Types::CodeStructureType::Function ||
            cst == OmniDocuGen::Types::CodeStructureType::Operator ||
            cst == OmniDocuGen::Types::CodeStructureType::Member ||
            cst == OmniDocuGen::Types::CodeStructureType::Typedef);
}

bool OmniDocuGen::Util::IsClassOrStruct(const OmniDocuGen::Types::CodeStructureType&  cst)
{
    return (cst == OmniDocuGen::Types::CodeStructureType::Class ||
            cst == OmniDocuGen::Types::CodeStructureType::Struct);
}

std::string OmniDocuGen::Util::ToString(const OmniDocuGen::Types::CodeStructureType& cst, bool useShortHand)
{
    if (!useShortHand) {
        return static_cast<std::string>(cst);
    }
    switch (cst) {
        case OmniDocuGen::Types::CodeStructureType::Namespace:
            return "NS";
        case OmniDocuGen::Types::CodeStructureType::Class:
            return "CLS";
        case OmniDocuGen::Types::CodeStructureType::Ctor:
            return "CTOR";
        case OmniDocuGen::Types::CodeStructureType::Dtor:
            return "DTOR";
        case OmniDocuGen::Types::CodeStructureType::Function:
            return "FN";
        case OmniDocuGen::Types::CodeStructureType::Operator:
            return "OPTR";
        case OmniDocuGen::Types::CodeStructureType::Member:
            return "MBR";
        case OmniDocuGen::Types::CodeStructureType::Typedef:
            return "TDEF";
        case OmniDocuGen::Types::CodeStructureType::Struct:
            return "STRCT";
        case OmniDocuGen::Types::CodeStructureType::Enum:
            return "ENUM";
        case OmniDocuGen::Types::CodeStructureType::File:
            return "FILE";
        case OmniDocuGen::Types::CodeStructureType::Unknown:
            break;
    }
    return "UNK";
}

bool OmniDocuGen::Util::IsValidExt(const std::string& ext)
{
    if (ext.empty()) { return true; }
    return has(OmniDocuGen::Util::m_validExt,
                omni::string::trim(omni::string::to_lower(ext)));
}

bool OmniDocuGen::Util::IsSourceExt(const std::string& ext)
{
    std::string r = omni::string::trim(omni::string::to_lower(ext));
    return (r == ".cpp" || r == ".cxx");
}

bool OmniDocuGen::Util::IsHeaderExt(const std::string& ext)
{
    std::string r = omni::string::trim_end(ext);
    if (r.length() > 3) { r = omni::string::to_lower(r.substr(r.length() - 4)); }
    return (r == ".hpp" || r == ".hxx");
}

bool OmniDocuGen::Util::IsCExtension(const std::string& ext)
{
    return has(OmniDocuGen::Util::m_cExt,
                omni::string::trim(omni::string::to_lower(ext)));
}