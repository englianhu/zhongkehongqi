# Rime输入法Emoji与符号滤镜

#### 最新更新（仅记录大更新）
2020.04.06 新增Emoji13.0更新内容，各操作系统平台还未更新，所以可能会是乱码，不用在意。  
　　　　　增加微信中对一些Emoji的中文释义  
2019.10.29 iOS13.2的新增Emoji表情内容更新

#### 项目介绍
GitHub地址：https://github.com/rtransformation/rime-opencc_emoji_symbols  
利用OpenCC做的Emoji和特殊符号滤镜，供Rime输入法使用者使用。  
基本包含Emoji 12.0的所有内容（包括同一人物类Emoji的5个不同肤色版本）。


#### 使用方法

将es.txt和es.json放入Rime输入法的opencc文件夹下。  
在你所使用的方案的xxxx.schema.yaml文件的「相应」位置加入如下代码（注意缩进）：

```
switches:
  - name: show_es
    reset: 1
    states: [ 😔, 😀 ]

engine:
  filters:
    - simplifier@es_conversion

es_conversion:
  opencc_config: es.json
  option_name: show_es

```


加入后重新部署，就可以使用了。
