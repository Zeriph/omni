tfile="template.hpp"
lfile="license.txt"
outdir="delegate"
cnt=16
verbose=0
evpnumptf1=""
evpnumpt1=""
evpnumptf=""
evpnumpt=""
evpnumtdef=""
evpnumtdoxdef=""
evpnumdata=""
evpnumdataval=""
evpnumdatavalvar=""
evpnumvals=""
lineending="rn"
wasdirset=false
set wshell = wscript.createobject("WScript.Shell")
set objFSO = createobject("Scripting.FileSystemObject")

if wscript.arguments.count > 1 then
    for i = 0 to wscript.arguments.count - 1
        arg1 = lcase(wscript.arguments(i))
        i = i + 1
        if i < wscript.arguments.count then
            arg2 = wscript.arguments(i)
        end if
        if arg1 = "-f" then    
            tfile=arg2            
        elseif arg1 = "-d" then
            outdir=arg2
            wasdirset=true
        elseif arg1 = "-n" then
            cnt=arg2
        elseif arg1 = "-l" then
            lfile=arg2
        elseif arg1 = "-le" then
            lineending=arg2
        else
            usage
            wscript.quit
        end if
    next
end if

' Parse args
if wasdirset = false then
    outdir=inputbox("Please enter the output directory")
end if
if outdir = "" then
    msgbox "A direcotry was not set"
    wscript.quit
end if
if not objFSO.FolderExists(outdir) then
    res=msgbox("Directory " & outdir & " does not exist, create?", vbYesNo)
    if res = vbYes then
        objFSO.CreateFolder(outdir)
    end if
end if
if not objFSO.FolderExists(outdir) then
    msgbox "Output directory not found: " & outdir
    wscript.quit
end if
if not objFSO.FileExists(tfile) then
    msgbox "Input file not found: " & tfile
    wscript.quit
end if
if cnt < 2 then
    cnt=2
end if
if lineending <> "r" and lineending <> "n" and lineending <> "rn" then
    lineending="rn"
end if

' INPUT: tfile
' OUTDIR: outdir
' MAX TEMPLATED ARG COUNT: cnt
set oTS = objFSO.OpenTextFile(tfile)
template = oTS.ReadAll
oTS.close
set oTS = nothing
gend=0

msgbox "Input file: " & tfile & vbcrlf & _
       "Output directory: " & outdir & vbcrlf & _
       "Max template argument count: " & cnt & vbcrlf & _
       "Line endings: " & lineending

lineending=replace(lineending, "r", vbcr)
lineending=replace(lineending, "n", vblf)

for num = 1 to cnt
    ofile=outdir & "\delegate\" & num & ".hpp"
    ptX=""
    ptX1=""
    ptX_t=""
    evpnumptf1=""
    evpnumpt1=""
    evpnumptf=""
    evpnumpt=""
    evpnumtdef=""
    evpnumtdoxdef=""
    evpnumdata=""
    evpnumdataval=""
    evpnumdatavalvar=""
    evpnumvals=""
    for tnum = 1 to num
        ptX="PT" & tnum
        ptX1="PT1_" & tnum
        ptX_t="p" & tnum & "_t"
        evpnumptf1=evpnumptf1 & ptX1
        evpnumpt1=evpnumpt1 & "typename " & ptX1
        evpnumptf=evpnumptf & ptX
        evpnumpt=evpnumpt & "typename " & ptX
        if tnum < 4 then
            if tnum = 1 then
                evpnumtdoxdef=evpnumtdoxdef & "     * @tparam " & ptX & "     Specifies the 1st parameter type passed to the function delegate" & vblf
                evpnumtdef=evpnumtdef & "            /** Defines the 1st function parameter type of this delegate */" & vblf
            elseif tnum = 2 then
                evpnumtdoxdef=evpnumtdoxdef & "     * @tparam " & ptX & "     Specifies the 2nd parameter type passed to the function delegate" & vblf
                evpnumtdef=evpnumtdef & "            /** Defines the 2nd function parameter type of this delegate */" & vblf
            elseif tnum = 3 then
                evpnumtdoxdef=evpnumtdoxdef & "     * @tparam " & ptX & "     Specifies the 3rd parameter type passed to the function delegate" & vblf
                evpnumtdef=evpnumtdef & "            /** Defines the 3rd function parameter type of this delegate */" & vblf
            end if      
            evpnumtdef=evpnumtdef & "            typedef " & ptX & " " & ptX_t & ";" & vblf
        else
            evpnumtdoxdef=evpnumtdoxdef & "     * @tparam " & ptX & "     Specifies the " & tnum & "th parameter type passed to the function delegate" & vblf
            evpnumtdef=evpnumtdef & "            /** Defines the " & tnum & "th function parameter type of this delegate */" & vblf
            evpnumtdef=evpnumtdef & "            typedef " & ptX & " " & ptX_t & ";" & vblf
        end if
        evpnumdata=evpnumdata & ptX_t
        evpnumdataval=evpnumdataval & ptX_t & " val" & tnum
        evpnumdatavalvar=evpnumdatavalvar & "val" & tnum
        evpnumvals=evpnumvals & "void*"
        if tnum <= (num-1) then
            evpnumptf1=evpnumptf1 & ", "
            evpnumpt1=evpnumpt1 & ", "
            evpnumptf=evpnumptf & ", "
            evpnumpt=evpnumpt & ", "
            evpnumdata=evpnumdata & ", "
            evpnumdataval=evpnumdataval & ", "
            evpnumdatavalvar=evpnumdatavalvar & ", "
            evpnumvals=evpnumvals & ", "
        end if
    next

    if objFSO.FileExists(ofile) then
        objFSO.DeleteFile(ofile)
    end if
    
    tplate=template
    tplate=replace(tplate, "PNUMVALS", evpnumvals)
    tplate=replace(tplate, "PNUMPTF1", evpnumptf1)
    tplate=replace(tplate, "PNUMPT1", evpnumpt1)
    tplate=replace(tplate, "PNUMPTF", evpnumptf)
    tplate=replace(tplate, "PNUMPT", evpnumpt)
    tplate=replace(tplate, "PNUMDATAVALVAR", evpnumdatavalvar)
    tplate=replace(tplate, "PNUMDATAVAL", evpnumdataval)
    tplate=replace(tplate, "PNUMDATA", evpnumdata)
    tplate=replace(tplate, "PNUMTDEF", evpnumtdef)
    tplate=replace(tplate, "PNUMTDOXDEF", evpnumtdoxdef)
    tplate=replace(tplate, "PNUM", num)
    tplate=replace(tplate, vblf, lineending)
    
    set otfile = objFSO.CreateTextFile(ofile, 2, True)
    otfile.Write(tplate)
    otfile.Close
    
    if objFSO.FileExists(ofile) then
        gend = gend + 1
    end if
next

msgbox "Generated " & gend & " header files"

makehpp

'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
function usage()
    msgbox "usage: delmkr.vbs [-f INPUT] [-d OUTDIR] [-n NUM] [-l LFILE] [-le r,n,rn]" & vbcrlf & _
           vbcrlf & _
           "FLAGS:" & vbcrlf & _
           "   -f INPUT       Specifies an input file" & vbcrlf & _
           "                  default: " & tfile & vbcrlf & _
           "   -d OUTDIR      Specifies the output directory for the headers" & vbcrlf & _
           "                  default: " & outdir & vbcrlf & _
           "   -n NUM         The max number of delegates you wish to create" & vbcrlf & _
           "                  default: " & cnt & vbcrlf & _
           "   -l LFILE       Specifies the license file to use for delegates.hpp" & vbcrlf & _
           "                  default: " & lfile & vbcrlf & _
           "   -le r,n,rn     The line ending you wish to use on the generated files" & vbcrlf & _
           "                  default: " & lineending
end function

function makehpp()
    set oTS = objFSO.OpenTextFile(lfile)
    otxt = oTS.ReadAll
    oTS.close
    set oTS = nothing
    ofile=outdir & "\delegates.hpp"
    
    msgbox "Generating " & ofile
    
    if objFSO.FileExists(ofile) then
        objFSO.DeleteFile(ofile)
    end if
    
    otxt = otxt & vblf & _
       "#if !defined(OMNI_DELEGATES_HPP)" & vblf _
       "#define OMNI_DELEGATES_HPP 1" & vblf & vblf
    for tnum = 0 to cnt
        otxt = otxt & "#include <omni/delegate/" & tnum & ".hpp>" & vblf
    next
    otxt = otxt & vblf _
    otxt = otxt & "#endif // OMNI_DELEGATES_HPP" & vblf
    
    set otfile = objFSO.CreateTextFile(ofile, 2, True)
    otfile.Write(otxt)
    otfile.Close
    
    if not objFSO.FileExists(ofile) then
        msgbox "Could not generate " & ofile
    end if
end function