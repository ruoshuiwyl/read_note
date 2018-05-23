# 大规模分布式存储系统
## 单机存储引擎
-  哈希存储 键值存储系统
-  B树存储  关系数据库 MySQL InnoDB
-  LSM树存储 levelDB
## 事务与并发控制
- 原子性
- 一致性
- 隔离性  
- 持久性

隔离级别：
- RU
- RC
- RR
- S
  
异常：
- LU
- DR
- NRR
- SLU
- PR

> 隔离级别与读写异常

|    | LU | DR | NRR | SLU | PR |
| -- | -- | -- |  -- | --  | -- |
| RU | N  | Y  | Y  | Y  | Y  |
| RC | N  | N  | Y  | Y  | Y  |
| RR | N  | N  | N  | N  | Y  |
| S  | N  | N  | N  | N  | N  |
