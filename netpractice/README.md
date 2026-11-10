[← Back to 42 Common Core](../README.md)

<div align="center">
<table>
  <tr>
    <td colspan="5" align="center">🌐 netpractice 🌐</td>
  </tr>
  <tr>
    <td align="center">Project</td>
    <td align="center">Bonus</td>
    <td rowspan="2" align="center"><a href="#"><img width="200" src="https://github.com/user-attachments/assets/e2d89fea-98e5-459f-ae1a-c96f095f7107"></a></td>
  </tr>
  <tr>
    <td><a href="#"><img width="95" src="https://github.com/zcherif/42Cursus/assets/116104082/504507eb-65b0-4814-9525-a2c22100dab1"></a></td>
    <td><a href="#"><img width="100" src="https://github.com/zcherif/42Cursus/assets/116104082/0df7dd81-56fb-4929-a023-67c7386906dc"></a></td>
  </tr>
</table>

</div>

---

<div align=center>

|CIDR|Hosts|Mask|Calculations<br>(brcst+net)|Possible subnets|Subnet size|Valid IPs range<br> without brc/net|
|---|---|---|---|---|---|---|
|`/30`| `255.255.255.252` | `2` <br>hosts| MASK<br> 256 - 252 = 4 - 2 = `2` <br>CIDR<br> 32 - 30 = 2 <br>2^2 = 4 - 2 = `2` |30 - 24 = 6 <br> 2^6 = `64`|4 IPs|network: `192.168.1.0`<br>`192.168.1.1`<br>`192.168.1.2`<br>broadcast: `192.168.1.3`|
|`/29`| `255.255.255.248` | `6` <br>hosts| MASK<br> 256 - 248 = 8 - 2 = `6` <br>CIDR<br> 32 - 29 = 3 <br>2^3 = 8 - 2 = `6` |29 - 24 = 5 <br> 2^5 = `32`|8 IPs|network: `192.168.1.0`<br>`192.168.1.1`<br>`192.168.1.6`<br>broadcast: `192.168.1.7`|
|`/28`| `255.255.255.240` | `14` <br>hosts| MASK<br> 256 - 240 = 16 - 2 = `14` <br>CIDR<br> 32 - 28 = 4 <br>2^4 = 16 - 2 = `14` |28 - 24 = 4 <br> 2^4 = `16`|16 IPs|network: `192.168.1.0`<br>`192.168.1.1`<br>`192.168.1.14`<br>broadcast: `192.168.1.15`|
|`/27`| `255.255.255.224` | `30` <br>hosts| MASK<br> 256 - 224 = 32 - 2 = `30` <br>CIDR<br> 32 - 27 = 5 <br>2^5 = 32 - 2 = `30` |27 - 24 = 3 <br> 2^3 = `8`|32 IPs|network: `192.168.1.0`<br>`192.168.1.1`<br>`192.168.1.30`<br>broadcast: `192.168.1.31`|
|`/26`| `255.255.255.192` | `62` <br>hosts| MASK<br> 256 - 192 = 64 - 2 = `62` <br>CIDR<br> 32 - 26 = 6 <br>2^6 = 64 - 2 = `62` |26 - 24 = 2 <br> 2^2 = `4`|64 IPs|network: `192.168.1.0`<br>`192.168.1.1`<br>`192.168.1.62`<br>broadcast: `192.168.1.63`|
|`/25`| `255.255.255.128` | `126` <br>hosts| MASK<br> 256 - 128 = 128 - 2 = `126` <br>CIDR<br> 32 - 25 = 7 <br>2^7 = 128 - 2 = `126` |25 - 24 = 1 <br> 2^1 = `2`|128 IPs|network: `192.168.1.0`<br>`192.168.1.1`<br>`192.168.1.126`<br>broadcast: `192.168.1.127`|
|`/24`| `255.255.255.0` | `254` <br>hosts| MASK<br> 256 - 0 = 256 - 2 = `254` <br>CIDR<br> 32 - 24 = 8 <br>2^8 = 256 - 2 = `254` |24 - 24 = 0 <br> 2^0 = `1`|256 IPs|network: `192.168.1.0`<br>`192.168.1.1`<br>`192.168.1.254`<br>broadcast: `192.168.1.255`|


<img width="1435" height="422" alt="CIDR" src="https://github.com/user-attachments/assets/d65e58fa-b4d1-46d3-91ac-5facd82e780f" />


</div>







