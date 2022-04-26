<!--
 * @Author: your name
 * @Date: 2022-04-05 12:49:10
 * @LastEditTime: 2022-04-26 15:53:12
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \Cache\readme.md
-->
# 缓存实现
## Lru缓存
- 采用Lru算法在无空闲空间时淘汰近期未访问元素
- 采用守护进程后台动态清除过期元素

## Lfu缓存
- 采用Lfu算法在无空闲空间时淘汰近期未访问元素
- 采用守护进程后台动态清除过期元素