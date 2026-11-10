[← Back to 42 Common Core](../README.md)

<div align="center">

<table>
  <tr>
    <td colspan="4" align="center">🍽️ philosophers 🍽️</td>
  </tr>
  <tr>
    <td align="center">Project</td>
    <td align="center">Bonus</td>
    <td rowspan="2" align="center"><a href="#"><img width="250" src="https://github.com/user-attachments/assets/d806db09-6f09-4b12-b7f9-f7618ee58326"></a></td>
  </tr>
  <tr>
    <td><a href="#"><img width="100" src="https://github.com/zcherif/42Cursus/assets/116104082/504507eb-65b0-4814-9525-a2c22100dab1"></a></td>
    <td><a href="#"><img width="100" src="https://github.com/zcherif/42Cursus/assets/116104082/0df7dd81-56fb-4929-a023-67c7386906dc"></a></td>
  </tr>
</table>

</div>
</div>

<div text-align="left">
  
`````
t_table
│
├── nbr_phs     (Número de filósofos)
├── t_to_die    (Tiempo de muerte por inanición)
├── t_to_eat    (Tiempo que tarda en comer)
├── t_to_sleep  (Tiempo que tarda en dormir)
├── meals_req   (Número de comidas necesarias)
├── feast_end   (Señal de final de la simulación)
├── start_t     (Tiempo de inicio de la simulación)
│
├── forks       (Array de mutexes para los tenedores)
│   ├── forks[0] → t_mutex (Mutex para el tenedor 1)
│   ├── forks[1] → t_mutex (Mutex para el tenedor 2)
│   ├── ... 
│   └── forks[nbr_phs-1] → t_mutex (Mutex para el tenedor n)
│
├── start_thds  (Mutex de sincronización inicial)
├── print_m     (Mutex de acceso a imprimir)
├── data_m      (Mutex de acceso a los datos comunes)
│
└── philos      (Array de estructuras de filósofos)
    ├── philos[0] → t_philo
    │   ├── id            → 1
    │   ├── meals_eaten   → 0 (Ejemplo inicial)
    │   ├── feeded        → 0 (Ejemplo inicial)
    │   ├── last_meal     → 0 (Ejemplo inicial)
    │   ├── l_fork        → t_mutex (Mutex para el tenedor izquierdo)
    │   ├── r_fork        → t_mutex (Mutex para el tenedor derecho)
    │   ├── table         → t_table (Apunta de regreso a la estructura `t_table`)
    │   └── thd           → pthread_t (ID del hilo del filósofo 1)
    │
    ├── philos[1] → t_philo
    │   ├── id            → 2
    │   ├── meals_eaten   → 0 (Ejemplo inicial)
    │   ├── feeded        → 0 (Ejemplo inicial)
    │   ├── last_meal     → 0 (Ejemplo inicial)
    │   ├── l_fork        → t_mutex (Mutex para el tenedor izquierdo)
    │   ├── r_fork        → t_mutex (Mutex para el tenedor derecho)
    │   ├── table         → t_table (Apunta de regreso a la estructura `t_table`)
    │   └── thd           → pthread_t (ID del hilo del filósofo 2)
    │
    ├── ... 
    │
    └── philos[nbr_phs-1] → t_philo
        ├── id            → n
        ├── meals_eaten   → 0 (Ejemplo inicial)
        ├── feeded        → 0 (Ejemplo inicial)
        ├── last_meal     → 0 (Ejemplo inicial)
        ├── l_fork        → t_mutex (Mutex para el tenedor izquierdo)
        ├── r_fork        → t_mutex (Mutex para el tenedor derecho)
        ├── table         → t_table (Apunta de regreso a la estructura `t_table`)
        └── thd           → pthread_t (ID del hilo del filósofo n)
`````

</div>
