# 安装

> 使用alist挂载网盘，通过onlyoffice解决office文件预览的问题

## alist

```sh
docker run -d --restart=always -v /etc/alist:/opt/alist/data -p 5244:5244 -e PUID=0 -e PGID=0 -e UMASK=022 --name="alist" xhofe/alist:main
```

修改密码
```sh
# 进入容器后执行以下命令
83cbaa39bf72:/opt/alist# ls
alist  data
83cbaa39bf72:/opt/alist# ./alist admin
INFO[2023-05-06 06:48:19] reading config file: data/config.json        
INFO[2023-05-06 06:48:19] load config from env with prefix: ALIST_     
INFO[2023-05-06 06:48:19] init logrus...                               
INFO[2023-05-06 06:48:19] admin user's info: 
username: admin
password: EEL9Otl8 
83cbaa39bf72:/opt/alist# 
```

## onlyoffice

```sh
sudo docker run -i -t -d -p 80:80 --name onlyoffice \
    -v /app/onlyoffice/DocumentServer/logs:/var/log/onlyoffice  \
    -v /app/onlyoffice/DocumentServer/data:/var/www/onlyoffice/Data  \
    -v /app/onlyoffice/DocumentServer/lib:/var/lib/onlyoffice \
    -v /app/onlyoffice/DocumentServer/rabbitmq:/var/lib/rabbitmq \
    -v /app/onlyoffice/DocumentServer/redis:/var/lib/redis \
    -v /app/onlyoffice/DocumentServer/db:/var/lib/postgresql  onlyoffice/documentserver
```

# 文件预览配置


## onlyoffice

1. 进入容器，修改view.html预览文件，没有则创建

具体位置可以自行调整，这里以api.js同级为例，能访问即可。

```sh
docker exec -it e91769de8a2b /bin/bash
# 进入 view文件 位置
root@e91769de8a2b:/var/www/onlyoffice/documentserver/web-apps/apps/api/documents# pwd
/var/www/onlyoffice/documentserver/web-apps/apps/api/documents
root@e91769de8a2b:/var/www/onlyoffice/documentserver/web-apps/apps/api/documents# 
root@e91769de8a2b:/var/www/onlyoffice/documentserver/web-apps/apps/api/documents# cat view.html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>OnlyOffice Viewer</title>
</head>
 
<body>
    <div id="placeholder"></div>
    <script type="text/javascript" src="http://IP:onlyoffice_PORT/web-apps/apps/api/documents/api.js"></script>
    <script>
        function getQueryParamValue(name) {
            const searchParams = new URLSearchParams(window.location.search);
            return searchParams.get(name);
        }
        
        const url = decodeURIComponent(getQueryParamValue("src"));
        const fileName = url.substring(url.lastIndexOf('/') + 1, url.lastIndexOf('?') != -1 ? url.lastIndexOf('?') : url.length);
        const fileExtension = fileName.split('.').pop();
        const docEditor = new DocsAPI.DocEditor("placeholder", {
            "document": {
                "fileType": fileExtension,
                "permissions": {
                    "edit": true,
                    "comment": true,
                    "download": true,
                    "print": true,
                    "fillForms": true,
                },
                "title": fileName,
                "url": url,
            },
            "editorConfig": {
                "lang": "zh-CN",
                "mode": "view",
            },
            "height": "1080px",
            "type": "desktop",
        });
    </script>
</body>
</html>
root@e91769de8a2b:/var/www/onlyoffice/documentserver/web-apps/apps/api/documents# 
```

2. 测试api.js文件是否可以访问

    上述文件中的src根据需要根据情况自行替换IP和端口，访问链接后要求可以正确显示内容

<script type="text/javascript" src="http://IP:onlyoffice_PORT/web-apps/apps/api/documents/api.js"></script>

3. 测试view.html文件是否可以访问

```txt
http://IP:onlyoffice_PORT/web-apps/apps/api/documents/view.html
```

    出现如下提示弹窗后代表onlyoffice配置正确，可以进入alist管理页面配置

The "document.fileType" parameter for the config object is invalid. Please correct it.

4. 现有 onlyoffice:7.5.0.125 部署会出现下列问题

[![image.png](https://i.postimg.cc/jjJMyXW2/image.png)](https://postimg.cc/yJshH0yC)

具体解决方法如下

```sh
docker exec -it e91769de8a2b /bin/bash

cd /etc/onlyoffice/documentserver
sed -i 's/true/false/g' local.json  
supervisorctl restart all
```
## alist

1. 进入alist管理 -> 设置 -> 预览 -> Iframe

    在需要的文件类型下添加onlyoffice链接，其中?前面的为上述onlyoffice中配置的链接，?后面的为参数。具体内容如下。
```sh
http://IP:onlyoffice_PORT/web-apps/apps/api/documents/view.html?src=$e_url
```

```sh
{
	"doc,docx,xls,xlsx,ppt,pptx": {
		"onlyoffice":"http://IP:onlyoffice_PORT/web-apps/apps/api/documents/view.html?src=$e_url",
        "Google":"https://docs.google.com/gview?url=$e_url&embedded=true"
	},
	"pdf": {
        "onlyoffice":"http://IP:onlyoffice_PORT/web-apps/apps/api/documents/view.html?src=$e_url",
		"PDF.js":"https://alist-org.github.io/pdf.js/web/viewer.html?file=$e_url"
	},
	"epub": {
        "onlyoffice":"http://IP:onlyoffice_PORT/web-apps/apps/api/documents/view.html?src=$e_url",
		"EPUB.js":"https://alist-org.github.io/static/epub.js/viewer.html?url=$e_url"
	}
}
```

# 页面预览配置

1. 进入alist管理 -> 设置 -> 全局 -> 自定义头部

```sh
<script src="https://polyfill.io/v3/polyfill.min.js?features=String.prototype.replaceAll"></script>

<!--引入字体，全局字体使用-->
<link rel="stylesheet" href="https://npm.elemecdn.com/lxgw-wenkai-webfont@1.1.0/lxgwwenkai-regular.css" />

<!--不蒜子计数器-->
<script async src="https://busuanzi.icodeq.com/busuanzi.pure.mini.js"></script>


<style>
/*白天背景图
https://i.postimg.cc/wxChqCJS/13.png
*/
.hope-ui-light{
  background-image: url("https://i.postimg.cc/3wfvPVYf/17.png") !important;
  background-repeat:no-repeat;background-size:cover;background-attachment:fixed;background-position-x:center;
}
/*夜间背景图
https://i.postimg.cc/d1DrBsRW/15.png
*/
.hope-ui-dark {
    background-image: url("https://i.postimg.cc/ZYB8hb98/12.png") !important;
    background-repeat:no-repeat;background-size:cover;background-attachment:fixed;background-position-x:center;
}

/*主列表夜间模式透明，50%这数值是控制透明度大小的*/
.obj-box.hope-stack.hope-c-dhzjXW.hope-c-PJLV.hope-c-PJLV-iigjoxS-css{
background-color:rgb(0 0 0 / 50%) !important;
}
/*readme夜间模式透明，50%这数值是控制透明度大小的*/
.hope-c-PJLV.hope-c-PJLV-iiuDLME-css{
background-color:rgb(0 0 0 / 50%) !important;
}
/*主列表透明*/
.obj-box.hope-stack.hope-c-dhzjXW.hope-c-PJLV.hope-c-PJLV-igScBhH-css {
background-color: rgba(255, 255, 255, 0.5) !important;
}
/*readme透明*/
.hope-c-PJLV.hope-c-PJLV-ikSuVsl-css{
background-color: rgba(255, 255, 255, 0.5) !important;
}
/*顶部右上角切换按钮透明*/
.hope-c-ivMHWx-hZistB-cv.hope-icon-button{
background-color: rgba(255, 255, 255, 0.3) !important;
}
/*右下角侧边栏按钮透明*/
.hope-c-PJLV-ijgzmFG-css{
background-color: rgba(255, 255, 255, 0.5) !important;
}


/*白天模式代码块透明*/
.hope-ui-light pre{
    background-color: rgba(255, 255, 255, 0.1) !important;
}
/*夜间模式代码块透明*/
.hope-ui-dark pre {
    background-color: rgba(255, 255, 255, 0) !important;
}
/*全局字体*/
*{font-family:LXGW WenKai}
*{font-weight:bold}
body {font-family: LXGW WenKai;}

/*底部CSS，.APP .tanle这三个一起的*/
dibu {
    border-top: 0px;
    position: absolute;
    bottom: 0;
    width: 100%;
    margin: 0px;
    padding: 0px;
}
.App {
    min-height: 85vh;
}
.table {
    margin: auto;
}
/*去掉底部*/
.footer {
    display: none !important;
}
</style>
```

2. 进入alist管理 -> 设置 -> 全局 -> 自定义内容

```sh
<!--延迟加载-->
<!--如果要写自定义内容建议都加到这个延迟加载的范围内-->
<div id="customize" style="display: none;">
    <div>
        <br />
        <center class="dibu">
            <div style=" line-height: 20px;font-size: 11pt;font-weight: bold;">
                <span>
                    <span style="color: rgb(13, 109, 252);" id="hitokoto">
                        <a href="#" id="hitokoto_text">
                            "人生最大的遗憾,就是在最无能为力的时候遇到一个想要保护一生的人。"
                        </a>
                    </span> 
                </span>
                <p style="margin-left: 10rem;font-size: 10pt;color: rgb(13, 109, 252);">
                    <small>
                        —— My Sun
                    </small>
                </p>
            </div>
			<div style="font-size: 12px;">
                <span class="nav-item" style="color: rgb(13, 109, 252);">
					本"<span style="color: rgb(13, 109, 252); font-weight: bold;"><a href="#">目录</a></span>"访问量 <span id="busuanzi_value_page_pv" style="color: rgb(13, 109, 252); font-weight: bold;"></span> 次 本站总访问量 <span id="busuanzi_value_site_pv" style="color: rgb(13, 109, 252); font-weight: bold;"></span>                次 本站总访客数 <span id="busuanzi_value_site_uv" style="color: rgb(13, 109, 252); font-weight: bold;"></span> 人
				</span>
				<br />
				<!--版权，请尊重作者-->
                <span class="nav-item" style="color: rgb(13, 109, 252);">
                    <a class="nav-link" href="https://github.com/alist-org/alist" target="_blank">
                        <i class="fa-solid fa-copyright" style="color:#409EFF;" aria-hidden="true">
                        </i>
                        Alist | 
                    </a>
                </span>
                <!--后台入口-->
                <span class="nav-item" style="color: rgb(13, 109, 252);">
                    <a class="nav-link" href="/@manage" target="_blank">
                        <i class="fa-solid fa-folder-gear" style="color:#409EFF;" aria-hidden="true">
                        </i>
                        管理
                    </a>
                </span>
            </div>
        </center>
        <br />
        <br />
    </div>

    
<!--延迟加载范围到这里结束-->
</div>
<!--延迟加载配套使用JS-->
<script>
    let interval = setInterval(() => {
        if (document.querySelector(".footer")) {
            document.querySelector("#customize").style.display = "";
            clearInterval(interval);
        }
    }, 200);
</script>

<!-- 网页鼠标点击特效 - 蛛网 -->
<script>
	!function () {
    function n(n, e, t) {
        return n.getAttribute(e) || t
    }
 
    function e(n) {
        return document.getElementsByTagName(n)
    }
 
    function t() {
        var t = e("script"), o = t.length, i = t[o - 1];
        return {l: o, z: n(i, "zIndex", -1), o: n(i, "opacity", .5), c: n(i, "color", "0,0,0"), n: n(i, "count", 99)}
    }
 
    function o() {
        a = m.width = window.innerWidth || document.documentElement.clientWidth || document.body.clientWidth, c = m.height = window.innerHeight || document.documentElement.clientHeight || document.body.clientHeight
    }
 
    function i() {
        r.clearRect(0, 0, a, c);
        var n, e, t, o, m, l;
        s.forEach(function (i, x) {
            for (i.x += i.xa, i.y += i.ya, i.xa *= i.x > a || i.x < 0 ? -1 : 1, i.ya *= i.y > c || i.y < 0 ? -1 : 1, r.fillRect(i.x - .5, i.y - .5, 1, 1), e = x + 1; e < u.length; e++) n = u[e], null !== n.x && null !== n.y && (o = i.x - n.x, m = i.y - n.y, l = o * o + m * m, l < n.max && (n === y && l >= n.max / 2 && (i.x -= .03 * o, i.y -= .03 * m), t = (n.max - l) / n.max, r.beginPath(), r.lineWidth = t / 2, r.strokeStyle = "rgba(" + d.c + "," + (t + .2) + ")", r.moveTo(i.x, i.y), r.lineTo(n.x, n.y), r.stroke()))
        }), x(i)
    }
 
    var a, c, u, m = document.createElement("canvas"), d = t(), l = "c_n" + d.l, r = m.getContext("2d"),
        x = window.requestAnimationFrame || window.webkitRequestAnimationFrame || window.mozRequestAnimationFrame || window.oRequestAnimationFrame || window.msRequestAnimationFrame || function (n) {
            window.setTimeout(n, 1e3 / 45)
        }, w = Math.random, y = {x: null, y: null, max: 2e4};
    m.id = l, m.style.cssText = "position:fixed;top:0;left:0;z-index:" + d.z + ";opacity:" + d.o, e("body")[0].appendChild(m), o(), window.onresize = o, window.onmousemove = function (n) {
        n = n || window.event, y.x = n.clientX, y.y = n.clientY
    }, window.onmouseout = function () {
        y.x = null, y.y = null
    };
    for (var s = [], f = 0; d.n > f; f++) {
        var h = w() * a, g = w() * c, v = 2 * w() - 1, p = 2 * w() - 1;
        s.push({x: h, y: g, xa: v, ya: p, max: 6e3})
    }
    u = s.concat([y]), setTimeout(function () {
        i()
    }, 100)
}();
</script>
```

# nginx反向代理配置

> 配置之后，根据反向代理的规则，可分别通过http://ip 以及 https://ip 访问不同的服务

```sh
➜  ~ cat /etc/nginx/sites-available/default
##
# You should look at the following URL's in order to grasp a solid understanding
# of Nginx configuration files in order to fully unleash the power of Nginx.
# https://www.nginx.com/resources/wiki/start/
# https://www.nginx.com/resources/wiki/start/topics/tutorials/config_pitfalls/
# https://wiki.debian.org/Nginx/DirectoryStructure
#
# In most cases, administrators will remove this file from sites-enabled/ and
# leave it as reference inside of sites-available where it will continue to be
# updated by the nginx packaging team.
#
# This file will automatically load configuration files provided by other
# applications, such as Drupal or Wordpress. These applications will be made
# available underneath a path with that package name, such as /drupal8.
#
# Please see /usr/share/doc/nginx-doc/examples/ for more detailed examples.
##

# Default server configuration
#
#
# server {
#    listen 80;
#    server_name IP;
    # return 301 http://$host$request_uri;
    # return 301 https://$host$request_uri;
#}

server {
    listen 443 ssl;
    server_name IP;

    ssl_certificate /etc/ssl/certs/certificate_ca_bundle.crt;
    ssl_certificate_key /etc/ssl/private/private.key;

    location / {
        proxy_pass http://127.0.0.1:18778;
        proxy_set_header Host $host;
        proxy_set_header X-Real-IP $remote_addr;
        proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
		proxy_set_header Upgrade $http_upgrade;
		proxy_set_header Connection "upgrade";
		proxy_set_header Accept-Encoding gzip;
		proxy_http_version 1.1;
    }
}

server {
    listen 80;
    server_name IP;

    location / {
        proxy_pass http://127.0.0.1:19997;
        proxy_set_header Host $host;
        proxy_set_header X-Real-IP $remote_addr;
        proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
		proxy_set_header Upgrade $http_upgrade;
		proxy_set_header Connection "upgrade";
		proxy_set_header Accept-Encoding gzip;
		proxy_http_version 1.1;
    }
}
➜  ~ 
➜  ~ systemctl restart nginx.service
➜  ~ systemctl status nginx.service
```

# 参考链接

> https://alist.nn.ci/zh/

> https://hub.docker.com/r/onlyoffice/documentserver

> https://github.com/ONLYOFFICE/Docker-DocumentServer
