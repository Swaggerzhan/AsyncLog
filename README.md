# AsyncLog 

## 0x00 使用

example

```
cmake -DCMAKE_INSTALL_PREFIX=/安装路径
```

使用：

```C++
#include "include/Log.h"

int main() {
    LOG_INIT("logFilebaseName");
    
    Log(INFO) << "this is Log line";
    Log(DEBUG) << "this is another Log line";
    
    LOG_EXIT();
}
```

## 0x01 思路

使用Disruptor的并发编程模型实现的异步日志。[Disruptor](./)。