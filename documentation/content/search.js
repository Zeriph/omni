var stot = 0;
var maxResults = 50;

function searchTerm(html, file, npath, qry)
{
    const scont = '\<\!--start content--\>';
    var sidx = html.indexOf(scont);
    if (sidx >= 0) {
        sidx += scont.length;
        var eidx = html.indexOf('\<\!--end content--\>');
        var srch = stripHTML(html.substring(sidx, eidx));
        var slow = srch.toLowerCase();
        sidx = slow.indexOf(qry);
        if (sidx >= 0) {
            stot += 1;
            if (stot > maxResults) { return ''; }
            var ihtml = '<li class="srhcres">' + stot + '.) <b><a href="' + file + '">' + npath + '</a></b>:<br><font style="font-size:12px;">';
            var tmp = null;
            var tidx = null;
            while ((sidx < srch.length) && (sidx >= 0) && (ihtml.length < 400)) {
                sidx -= 30;
                if (sidx < 0) { sidx = 0; }
                else {
                    sidx = slow.indexOf(' ', sidx + 1) + 1;
                    ihtml += '...';
                }
                eidx = sidx + qry.length + 60;
                if (eidx > srch.length) { eidx = srch.length; }
                tmp = srch.substring(sidx, eidx);
                tmp = tmp.substring(0, tmp.lastIndexOf(' '));
                tidx = tmp.toLowerCase().indexOf(qry);
                ihtml += tmp.substring(0, tidx) + '<b>' + tmp.substring(tidx, (tidx+qry.length)) + '</b>' + tmp.substring((tidx+qry.length));
                if (eidx != srch.length) { ihtml += '...'; }
                sidx = slow.indexOf(qry, (sidx + 31));
            }
            return replaceAll(ihtml, '......', '...') + '</font></li><br>';
        }
    }
    return '';
}

function searchOnFile(opath, npath, qvals)
{
    var file = opath.replace('search.html', npath);
    var qlen = qvals.length;
    var ihtml = '';
    var xmlhttp;
    if (window.XMLHttpRequest) {
        xmlhttp = new XMLHttpRequest();
    } else {
        xmlhttp = new ActiveXObject("Microsoft.XMLHTTP");
    }
    try {
        window.title = "Omni C++ Library - Searching " + file;
        xmlhttp.open("GET", file, false);
        xmlhttp.send();
        for (var i = 0; i < qlen; ++i) {
            if (qvals[i] == '') { continue; }
            ihtml += searchTerm(xmlhttp.responseText, file, npath, qvals[i]);
        }
    } catch (err) {
        return;
    }
    if (stot <= maxResults) { document.getElementById('srchres').innerHTML += ihtml; }
}

function getQueryVals(qry)
{
    var idx = qry.indexOf('"');
    var qvals = null;
    if (idx >= 0) {
        qvals = [ ];
        var nvals = qry;
        while ((idx < nvals.length) && (idx >= 0)) {
            qvals[qvals.length] = nvals.substring(idx+1, nvals.indexOf('"', idx+1));
            nvals = nvals.replace('"' + qvals[qvals.length-1] + '"', '');
            idx = nvals.indexOf('"');
        }
        var tvals = nvals.split(' ');
        var tlen = tvals.length;
        for (var i = 0; i < tlen; ++i) { qvals[qvals.length] = tvals[i]; }
    } else {
        qvals = qry.split(' ');
    }
    return qvals;
}

function preformSearch()
{
    var qry = window.location.href.split('?search=');
    if (qry.length > 0 && qry[1] != null && qry[1] != '') {
        var sqry = decodeURIComponent(qry[1]);
        var qvals = getQueryVals(sqry.toLowerCase());
        var len = searchList.length;
        stot = 0;
        document.getElementById('omnisrch').value = sqry;
        document.getElementById('srchres').innerHTML = 'Searching for: <b>' + sqry + '</b><br><br>';
        for (var i = 0; i < len; ++i) {
            searchOnFile(qry[0], searchList[i], qvals);
        }
        if (stot > maxResults) { document.getElementById('srchres').innerHTML += "and " + (stot-maxResults) + " more...<br><br>"; }
    }
}
