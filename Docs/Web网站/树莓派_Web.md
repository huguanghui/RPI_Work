[TOC]

---
# H264+Nginx模块
## 软件安装

nginx源码包:
http://nginx.org/download/nginx-1.13.8.tar.gz

h264数据流支持包
http://h264.code-shop.com/download/nginx_mod_h264_streaming-2.2.7.tar.gz

## 安装步骤
### 依赖的安装
    sudo apt-get install libpcre3 libpcre3-dev
    sudo apt-get install openssl libssl-dev
    sudo apt-get install zlib1g-dev
### nginx和h264流模块
    wget http://nginx.org/download/nginx-1.13.8.tar.gz
    wget http://h264.code-shop.com/download/nginx_mod_h264_streaming-2.2.7.tar.gz
    

## 编译
    cd ~/nginx-1.13.8
    指定安装目录 --prefix=/usr/local/nginx-stream
    添加h264    --add-module=../nginx_mod_h264_streaming-2.2.7
    添加flv,mp4文件支持 --with-http_flv_module --with-http_mp4_module
    配置
    ./configure --prefix=/usr/local/nginx-stream --with-debug --with-http_dav_module --with-http_gzip_static_module --with-http_ssl_module --with-ipv6 --with-sha1=/usr/include/openssl --with-md5=/usr/include/openssl --add-module=../nginx_mod_h264_streaming-2.2.7 --with-http_flv_module --with-http_mp4_module
    make
    sudo make install

    编译错误解决
    1.nginx_mod_h264_streaming-2.2.7,修改ngx_http_streaming_module.c注释掉
    if (r->zero_in_uri)
    {
        return NGX_DECLINED;
    }
    2.删除Makefile文件中的-Werror

---