.
├── alink_export.h
├── board
│?? └── basic
│??     ├── demo
│??     │?? └── alink_sample.c        --->Alink sample代码
│??     ├── platform                  --->Alink抽象接口的参考实现
│??     │?? └── alink_ssl.c
│??     │?? └── alink_hardware.c
│??     └── product
│??         └──  alink_product.c             --->产品相关的接口，模组认证可以直接使用，无需修改。
├── json_parser.h                     --->Alink提供的json字符串解析相关的工具
├── lib_alink_Ameba1.a/lib_alink_AmebaZ.a                        --->Alink静态库
├── alink_platform.h                        --->Alink抽象接口的头文件，需要模组商实现
├── alink_product.h                         --->Alink产品相关的接口头文件
└── readme.txt


