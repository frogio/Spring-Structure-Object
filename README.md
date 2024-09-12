# Spring Structure Object
Hook의 법칙을 활용하여 Spring 오브젝트를 만들고, 이를 응용하여 로프, 천과 같은 매시브 스프링 구조를 만들어 보았다.

## 1. Spring Object
가장 기본적인 Spring Object, 스프링의 힘은 거리 변화량에 비례하며 힘에 단위 벡터를 곱해</br>
힘의 크기와 방향을 동시에 표현하였다</br>

기본적인 스프링 힘은 다음과 같다.

force vector = -k * Δl  * v</br>
Δl = (l0 - l) </br>
k = spring constant </br>
v = unit vector </br>

## 2. Lope Object

스프링을 1차원으로 연속해서 나열하여 로프를 구현하였다. </br>
로프 입자간 스프링으로 연결한 다음 </br>
로프의 변형을 방지하는 shear spring을 입자 한개씩 건너 뛰면서 연결하였다.
![_2024_09_12_20_45_06_330-ezgif com-video-to-gif-converter](https://github.com/user-attachments/assets/7f79c546-fe9d-4a88-ac22-d476618937f1)

## 3. Cloth Object

입자들을 스프링으로 2차원상에서 연결시킨 오브젝트 </br>
입자 하나당 천 구조를 이루는 Structure Spring,  </br
천의 변형을 방지하는 Shear Spring, </br>
마지막으로 접힘을 방지하는 Bending Spring </br>
을 연결하여 구성하였다. </br>

구현 도중 아래의 튜토리얼을 참고하였다. </br>
https://viscomp.alexandra.dk/index2fa7.html?p=147

![_2024_09_12_20_46_41_717-ezgif com-video-to-gif-converter](https://github.com/user-attachments/assets/b4773edb-0ea5-49d2-b00d-65d38a947ba0)


