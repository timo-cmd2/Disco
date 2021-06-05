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

### Execution planned

Icebear syntax layer (dsl) -> Icebear runtime preprocessor -> IL Transpiler -> IL Assembly -> post-execution domain replication
 
## Author and Licensing

The Icebear project built by Timo Sarkar Copyroght 2020 - 2021 (c) Licensed under the BSL-1.0
