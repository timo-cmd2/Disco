# Icebear
Icebear is a dynamic dsl programming-language for writing and deploying group-policies

## Sample syntax planned:

```
parameter syntax version 0.1
parameter target domain: "conto.so"
parameter denytaskmgr dword:1

administrative-template denytaskmgr  {
  location string: "Windows/Control Panel"
}
```
