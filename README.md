# DebugInfo

在使用 DebugView时，由于只能打印TRACE和OutputDebugString方式，但是OutputDebugString需要使用的转换过多，自己想着使用TRACE简单改了下，方便以后调试打印日志使用。

说明：
    增加FILEINFO 的宏是方便知道问题在哪个文件哪行，哪个功能函数里；
    增加DATEINFO 的宏是方便显示时间，其实用处不大；
    使用TRACE时，和使用printf方式类似即可。
