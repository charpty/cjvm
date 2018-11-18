## libzip
> https://github.com/nih-at/libzip

On Mac: NOTE use `-lzip`
```
make build && cd build
cmake -DBUILD_SHARED_LIBS=OFF -DENABLE_OPENSSL=OFF ..
make
```
or just 

```
brew install libzip
```


## SDS
> https://github.com/antirez/sds

On Mac: copy the source file "sds.h", "sds.c", "sdsalloc.h" into dep/sds


## ADLIST
> https://github.com/antirez/redis

On Mac: copy the source file "adlist.h", "adlist.c" into dep/adlist