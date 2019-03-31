curl -R -O http://www.lua.org/ftp/lua-5.3.5.tar.gz
tar xzf lua-5.3.5.tar.gz

cp -R lua-5.3.5 src/vendor

rm -rf lua-5.3.5
rm lua-5.3.5.tar.gz

(cd src/vendor/lua-5.3.5; make linux;)

cp src/vendor/lua-5.3.5/src/luac out/luac