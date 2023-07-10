---
title: myblog
date: YYYY-MM-DD HH:MM:SS
tags: 工作效率
categories: hexo
---

### 个人网站搭建

#### 环境:

Ubuntu18.04  node.js  npm gitee   

npm是Node.js的包管理工具，可以用来安装、卸载以及管理Node.js模块。npm是Node.js的默认包管理器，可以通过npm安装各种第三方模块。

#### step:

hexo init
npm install
npm install hexo-deployer-git --save

npm i --save hexo-wordcount


npm install https://github.com/CodeFalling/hexo-asset-image --save

hexo new "第一篇文章"
hexo new page "categories"
hexo new page "tags"
hexo new page "about"

hexo clean && hexo g && hexo s
hexo clean && hexo g && hexo d



#### 踩坑汇总:

**1.node版本冲突问题**

`删除/usr/loacl/bin 下软连接重复问题`

**2.npm安装问题**

`和网速影响很大 用魔法解决`

**3.github和coding 部署问题很多** 

`直接用gitee 需实名制`

**4.网页样式问题.css等路径不对,(本地显示和网络显示不一致问题)**

`url: https://glider110.gitee.io/glider #网址`

**5.matery主题代码块样式错误**

- 再配置问题url修改
- 远程仓库名和本地仓库名一致

**6.md问题图片显示问题?**

- 开启和.md文档同级的同名目录

  `post_asset_folder: true`

- 下载 `npm install https://github.com/CodeFalling/hexo-asset-image --save`
- [修改ndex.js](https://blog.csdn.net/weixin_44999716/article/details/112401495?app_version=5.15.6&csdn_share_tail=%7B%22type%22%3A%22blog%22%2C%22rType%22%3A%22article%22%2C%22rId%22%3A%22112401495%22%2C%22source%22%3A%22weixin_37055691%22%7D&utm_source=app)

**7.hexo init没反应**

 `有时候网速不行,反复测`





