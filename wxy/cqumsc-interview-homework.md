# site.zip

网站JavaWeb工程的压缩文件，不包含数据库。  

数据库大概长这个样子：  

- 表`properties`：用于记录一些配置信息（有一堆字符串不知道放哪里就干脆整了张表）

|字段名|介绍|
|-----|-----|
|name|配置信息的名字|
|value|配置信息的值|

- 表`contents`：用于记录每一个页面

|字段名|介绍|
|-----|-----|
|name|名字|
|title|标题|
|introduction|简要介绍|
|image|在主页上显示的图片的链接|
|displayMethod|以何种方式显示|
|displayLevel|页面的链接在哪里出现|
|url|链接，但不一定是URL路径，和displayMethod有关|
|category|分类，用分号隔开|
|date|创建日期|
  
|displayMethod|介绍|
|-----|-----|
|link|url指向的网址出现在网页侧边的友情链接里面|
|index|一张导航页面，列出了所有category中含有url的所有页面|
|rawhtml|纯HTML文件，直接嵌入模板，url是文件路径|
|markdown|markdown文件，即时编译之后嵌入模板，url是文件路径|
  
|displayLevel|介绍|
|-----|-----|
|index|显示在导航页面（就是displayMethod为index的页面）里|
|navbar|直接显示在网页最上边的导航栏里|

# cqumsc-interview-homework.html 和 cqumsc-interview-homework.md

三个小任务的页面和网站说明。  

三个小任务的关键代码（JS）：
```javascript
// 十进制转罗马数字
function toRoman(dec) {
    var map = [[1, 'I', 'V'], [10, 'X', 'L'], [100, 'C', 'D'], [1000, 'M']];
    if (dec < 1 || dec > 3999) {
        return [false, "数字超出范围"];
    }
    ans = "";
    for (var i = 3; i != -1; i--) {
        var num = Math.floor(dec / map[i][0]);
        if (num == 0) {
            continue;
        }
        if (1 <= num && num <= 3) {
            // I, II, III
            ans += map[i][1].repeat(num);
        } else if (num <= 5) {
            // IV, V
            ans += map[i][1].repeat(5 - num) + map[i][2];
        } else if (num <= 8) {
            // VI, VII, VIII
            ans += map[i][2] + map[i][1].repeat(num - 5);
        } else {
            // IX, X
            ans += map[i][1].repeat(10 - num) + map[i + 1][1];
        }
        dec -= num * map[i][0];
    }
    return [true, ans];
}
// 罗马数字转十进制
function toDecimal(rom) {
    var map = {'I': 1, 'V': 5, 'X': 10, 'L': 50, 'C': 100, 'D': 500, 'M': 1000};
    var max_num = 1, ans = 0;
    for (var i = rom.length - 1; i != -1; i--) {
        var chr = rom.charAt(i);
        if (!(chr in map)) {
            return [false, "罗马数字中不应该出现字符'" + chr + "'"];
        }
        var num = map[chr];
        ans += (num < max_num ? -1 : 1) * num;
        max_num = Math.max(max_num, num);
    }
    var correct = toRoman(ans);
    if (!correct[0]) {
        return correct;
    }
    if (rom != correct[1]) {
        return [false, "格式错误，是不是应该是（" + correct[1] + "）？"];
    }
    return [true, ans];
}
// 从字符串解析矩阵，返回false代表解析失败
function parseMatrix(str) {
    var mat = [];
    $.each(str.trim().split(/\n+/), function (i, row) {
        var error_flag = false;
        mat[i] = [];
        $.each(row.trim().split(/\s+/), function (j, val) {
            error_flag |= isNaN(mat[i][j] = Number(val));
        });
        if (error_flag || mat[i].length != mat[0].length) {
            return false;
        }
    });
    return mat;
}
// 矩阵加法
function matPlus(mat1, mat2) {
    if (mat1.length != mat2.length || mat1[0].length != mat2[0].length) {
        return [false, "非同型矩阵之间不能进行加法"];
    }
    var res = [];
    $.each(mat1, function (i, row) {
        res[i] = [];
        $.each(row, function (j, val) {
            res[i][j] = val + mat2[i][j];
        });
    });
    return [true, res];
}
function matMult(mat1, mat2) {
    if (mat1[0].length != mat2.length) {
        return [false, "左侧矩阵的列数必须等于右侧矩阵的行数"];
    }
    var res = [];
    for (var i = 0; i < mat1.length; i++) {
        res[i] = [];
        for (var j = 0; j < mat2[0].length; j++) {
            res[i][j] = 0;
            for (var k = 0; k < mat2.length; k++) {
                res[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
    return [true, res];
}
// 工具：跨站HTML访问
function xsGet(url, callback) {
    $.ajax({
        type: 'GET',
        url: url,
        success: callback
    });
}
// 获得下一个成语
function nextWord(last, word, callback) {
    if (last.length != 0 && (last.substr(-1) != word.charAt(0))) {
        callback(false, "第一个字应该是 " + last.substr(-1), last);
    }
    var url = "https://chengyu.911cha.com/zi" + word.charCodeAt(0).toString(16) + "_1.html";
    xsGet(url, function (html) {
        if (!RegExp('<em>' + word.charAt(0) + '</em>' + word.substr(1)).test(html)) {
            callback(false, "这不是个成语", last);
        }
        var code = word.charCodeAt(word.length - 1).toString(16);
        xsGet("https://chengyu.911cha.com/zi" + code + "_1.html", function (html) {
            var nxt = /<em>(.+?)<\/em>(.+?)</.exec(html);
            var result = nxt[1] + nxt[2];
            callback(true, (nxt == null ? "接不下去了……" : result), (nxt == null ? '' : result));
        });
    });
}

```

# Bugs

1. 成语接龙的JS代码中有跨站访问请求，可能会被ban。

2. 成语接龙使用的API最多只能列出50条成语，所以会出现误判用户输入不是成语的情况。


