function flipStyle(id) {
    var elm = document.getElementById(id);
    elm.style.display = ((elm.style.display == 'none') ? 'block' : 'none');
}

function flipVis(id) {
    var elm = document.getElementById(id);
    elm.style.visibility = ((elm.style.visibility == 'hidden') ? 'visibile' : 'hidden');
}

function popup(code) {
    window.open(code);
    return false;
}

function collapse(id, rpath) {
    return;
    flipStyle('cmnts' + id);
    flipStyle('cmntl' + id);
    flipStyle('cmnt' + id);
    var ndiv = document.getElementById('cmnt' + id).nextSibling;
    var cdiv = document.getElementById('cmnts' + id).nextSibling;
    var img = document.getElementById('cmnti' + id);
    if (img.src.indexOf('min.gif') == -1) {
        img.src = rpath + 'content/tree/min.gif';
        img.className = "";
        ndiv.className = "";
        cdiv.className = "";
    } else {
        img.className = "c";
        ndiv.className = "c";
        cdiv.className = "c";
        img.src = rpath + 'content/tree/pls.gif';
    }
}

function collapseAll(maxid, rpath) {
    for (var i = 1; i <= maxid; ++i) {
        collapse(i, rpath);
    }
}

function replaceAll(str, find, replace) {
    return str.replace(new RegExp(find.replace(/([.*+?^=!:${}()|\[\]\/\\])/g, "\\$1"), 'g'), replace);
}

function stripHTML(txt) {
   var t = document.createElement('div');
   t.innerHTML = txt;
   return t.textContent || t.innerText || '';
}

function doSearch() {
    var sval = document.getElementById('omnisrch').value;
    if (sval == '') { alert('Please enter a search value'); }
    else {
        var sloc = document.getElementsByTagName('script')[0].src.replace('content/common.js', '');
        var locs = window.location.href.replace(sloc, '').split('/');
        var nloc = 'search.html?search=' + sval;
        for (var i = 0; i < locs.length-1; ++i) {
            nloc = '../' + nloc;
        }
        window.location = nloc;
    }
    return false;
}

function loadJS(userCallback) {
    var nojs = document.getElementById('srchli');
    var srch = document.getElementById('srchfrm');
    var simg = srch.getElementsByTagName('img')[0];
    var sfrm = srch.getElementsByTagName('form')[0];
    srch.title = nojs.title;
    simg.title = srch.title;
    nojs.style.display = 'none';
    srch.className = 'search_js';
    if (sfrm.addEventListener) {
        sfrm.addEventListener('submit', doSearch, false);  //Modern browsers
    } else if (sfrm.attachEvent) {
        sfrm.attachEvent('onsubmit', doSearch);            //Old IE
    }
    if (simg.addEventListener) {
        simg.addEventListener('click', doSearch, false);  //Modern browsers
    } else if (simg.attachEvent) {
        simg.attachEvent('onclick', doSearch);            //Old IE
    }
    if (userCallback && (typeof userCallback == "function")) { userCallback(); }
}
