# Smooth Blink Led
## Piscando um LED usando PWM - Exemplo 1
 
Estou usando o Arduino Uno então é necessario se atentar aos pinos, pois nem todas as portas são PWM. Nessa imagem você consegue ver quais portas possuem PWM:

<div align="center">
<img src = "https://user-images.githubusercontent.com/93883349/215360535-93567018-0b98-4262-aa3a-e903844f63fd.png" width="800"/>
  
  Fonte: https://docs.arduino.cc/hardware/uno-rev3
</div>


Aqui eu escolhi a porta 11, então criei um **define** para esse pino. Essa é uma abordagem que sempre recomendo, pois facilita a portabilidade do código para outras placas. 
```
#define SMOOTH_LED 11
```

Criei também um define para os intervalos de tempo do PWM, como uso esse valor em varios pontos isso facilita mudar a temporização sem causar bugs.
```
#define TIMER_DELAY 10
```

Eu sempre evito usar a função **delay()** em meus códigos, pois em projetos mais complexos isso pode literalmente travar o código por alguns instantes e causar problemas. Então como alternativa, uso a função **millis()** que pega o tempo em milissegundo naquele momento onde a função é chamada. Com algumas variaveis é possivel comparar o intervalo e saber qual o tempo exato e assim substituir o delay. 

Aqui eu faço exatamente isso, primeiro eu criei uma variavel do tipo **long**, pois o valor é em milissegundo e pode ser um valor bem grande e não caber em uma variavel do tipo **int**:
```
long timer = 0;
```
Então através do **if** eu consigo saber se o tempo que passou é maior que o **define** que eu criei anteriormente. Vale ressaltar que para funcionar bem, sempre que entrar no **if** a variavel deve ser carregada com o valor de **millis()** (linha 3).

Sempre que estou no **if** "escrevo" no pino do microcontrolador (linha 5) e incremento o valor da variavel **pwmValue** (linha 6), dessa forma o LED vai acendendo aos poucos. 

```
1  if (((millis() - timer) > TIMER_DELAY) && ledStatus == false)
2  { 
3     timer = millis();
4
5     analogWrite(SMOOTH_LED, pwmValue);
6     pwmValue++;
7
8    pwmValue == 255 ? ledStatus = true: ledStatus = false;
9  }
```
Na condição do **if** tem uma flag: **ledStatus** que é iniciada como falsa e só fica verdadeira quando o valor de **pwmValue** chega a 255.
Usando a operação ternária, consigo setar essa flag:
```
pwmValue == 255 ? ledStatus = true: ledStatus = false;
```
A operação ternária funciona basicamente como um **if e else**, mas tudo isso em uma unica linha:
```
condição ? se verdadeiro : se falso
```
Para apagar o LED a operação é exatamente ao contrário. Ao invés de incrementar o valor eu decremento até 0. Aqui que entra a flag **ledStatus**, evitando que durante o loop entre no **if** anterior.

```
1  if (((millis() - timer) > TIMER_DELAY) && ledStatus == true)
2  { 
3    timer = millis();
4
5    analogWrite(SMOOTH_LED, pwmValue);
6    pwmValue--;
7
8    pwmValue == 0 ? ledStatus = false: ledStatus = true;
9  }
```
Quando o valor zerar a flag volta ao status de falsa e o LED voltará a acender.

## Exemplo 2
Confesso que o ChatGPT me deu um bom norte nessa solução, reduzindo um pouco as linhas de código. Mas a solução 1 permite criar duas funções, uma para ligar e outra para desligar o LED, então não é totalmente descartada. Mas a solução 2 permite em algumas linhas fazer o LED acender e apagar de forma gradual, assim como no GIF no final.

```
1    if ((millis() - timer) > TIMER_DELAY)
2    { 
3       timer = millis();
4
5       pwmValue = pwmValue + brightnessDirection;
6
7       if (pwmValue == 0 || pwmValue == 255) 
8       {
9         brightnessDirection = -brightnessDirection;
10      }
11      analogWrite(SMOOTH_LED, pwmValue);
12    }
```

A parte do **millis()** permanece, assim o código segue sem travar. O que vem a mais é a variavel **brightnessDirection**. Na linha 5 a variavel **pwmValue** recebe o valor dela mesma e a **direção**. Se o valor da direção for positivo o LED está acendendo e em caso negativo o LED está apagando. No **if** da linha 7 é verificado se o valor está em zero ou 255 e então a direção muda. 

Caso sua intenção é apenas acender e apagar, essa solução é mais simples.

Ao final, se tudo der certo você vai ter um resultado assim:
<div align="center">
<img src = "https://user-images.githubusercontent.com/93883349/215351521-ebba2691-ed0d-4ef0-b004-1ef6d652f6f7.gif"/>
</div>

