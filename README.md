# Icebear
Icebear is a dynamic dsl programming-language for writing and deploying group-policies

## Goals of Icebear

- unified management of group-policies
- full-control layer instead of a limited interface (gpedit.msc)
- intuitive feeling over a custom programming-language
- built-in wmic querying and embedded syntax support
- pain-less and quick deployment 

## Non-Goals of Icebear

- be a general-purpose language
- usage beyond Microsoft Group-policy management
- cross-platform support (only win-based)

## Sample syntax planned:

```
parameter syntax version 0.1
parameter target domain: "conto.so"
parameter denytaskmgr dword:1

administrative-template denytaskmgr  {
  location string: "Windows/Control Panel"
}
```
 
## Author and Licensing

The Icebear project built by Timo Sarkar Copyright 2020 - 2021 (c) Licensed under the BSL-1.0
