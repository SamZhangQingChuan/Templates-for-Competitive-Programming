- 开场定义编译的 alias
- 所有都用 ll
- 尽量不使用 `i`, `j`, `k`
- $Inf$ 太小
- 数据范围，特殊数字
- 函数没有返回值，用编译选项检测
- 内层循环变量覆盖了外层循环变量
- 想想容斥
- 读 clarification
- INF 不够大
- 交完题目后立马打印随后让出机器
- 最后半小时不能慌张
- 文件交错？
- 删 debug 信息
- 答案格式
- 小数据暴力
- 程序版本提交错误
- 重新读题
- 重新写一遍
- 及时取模
- 取消同步后混用

```bash
alias gao=g++ -O2 -Wall -Wextra -pedantic -Wshadow -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -fsanitize=address -fsanitize=undefined
```

``` bash
while true; do
  ./generate > input
  ./run < input > output
  ./std < input > answer
  if diff output answer; then
    echo OK
  else
    echo WA
    break
  fi
done
```

