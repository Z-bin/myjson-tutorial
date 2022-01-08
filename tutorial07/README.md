- 宏的编写技巧

  当C语言的宏定义包含多余一条语句时，就需要`do { /*...*/} while(0)`包裹成单个语句，否则会有如下问题：

  ```C
  #define M() a(); b()
  if (cond)
      M();
  else
      c();
  
  /*预处理后*/
  if (cond)
      a(); b(); /* b();在if语句之外*/
  else		  /* 报错误：else without a previous ‘if’*/
      c();
  
  ```

  ​	只用`{}`也不行

  ```C
  #define M() { a(); b(); }
  
  /* 预处理后 */
  
  if (cond)
      { a(); b(); }; /* 最后的分号代表 if 语句结束 */
  else               /* else 缺乏对应 if */
      c();
  ```

  用 do while 就行了：

  ```C
  #define M() do { a(); b(); } while(0)
  
  /* 预处理后 */
  
  if (cond)
      do { a(); b(); } while(0);
  else
      c();
  ```

  