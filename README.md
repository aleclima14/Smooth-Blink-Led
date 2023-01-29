# Smooth BlinkLed
Piscando um LED usando PWM

![blink led](https://user-images.githubusercontent.com/93883349/215351521-ebba2691-ed0d-4ef0-b004-1ef6d652f6f7.gif)

Estou usando o Arduino Uno então é necessario se atentar aos pinos, pois nem todas as portas são PWM. Aqui eu escolhi a porta 11, então criei um **define** para esse pino. Essa é uma abordagem que sempre recomendo, pois facilita a portabilidade do código para outras placas. 
```
#define SMOOTH_LED 11
```

Criei também um define para os intervalos do PWM, como uso esse valor em varios pontos isso facilita mudar a temporização sem causar bugs.
```
#define TIMER_DELAY 10
```

Eu sempre evito usar a função **delay()** em meus códigos, pois em projetos mais complexos isso pode literalmente travar o código por alguns instantes e causar problemas. Então como alternativa, uso a função **millis()** que pega o tempo em milissegundo naquele momento onde a função é chamada. Com algumas variaveis é possivel comparar o intervalo e saber qual o tempo exato e assim substituir o delay. 

Aqui eu faço exatamente isso, primeiro eu criei uma variavel do tipo **long**, pois o valor é em milissegundo e pode ser um valor bem grande e não caber em uma variavel do tipo **int**:
```
long timer = 0;
```
Então através do **if** eu consigo saber se o tempo que passou é maior que o **define** que eu criei anteriormente. Vale ressaltar que para funcionar bem, sempre que entrar no **if** a variavel deve ser carregada com o valor de **millis()**.

Sempre que estou no **if** eu incremento o valor da variavel **pwmValue** e "escrevo" no pino do microcontrolador, dessa forma o LED vai acendendo aos poucos. 

```
if (((millis() - timer) > TIMER_DELAY) && ledStatus == false)
  { 
    timer = millis();

    analogWrite(SMOOTH_LED, pwmValue);
    pwmValue++;

    pwmValue == 255 ? ledStatus = true: ledStatus = false;
  }
```
Na condição do **if** tem uma flag: ledStatus que é iniciada como falsa e só fica verdadeira quando o valor de pwmValue chega a 255.
Usando a operação ternária, consigo setar essa flag:
```
pwmValue == 255 ? ledStatus = true: ledStatus = false;
```
A operação ternária funciona basicamente como um **if e else**, mas tudo isso em uma unica linha:
```
**condição** ? **se verdadeiro** : **se falso**
```
Para apagar o LED a operação é exatamente ao contrário. Ao invés de incrementar o valor, eu decremento até 0. Aqui que entra a flag **ledStatus**, evitando que durante o loop entre no **if**.

```
if (((millis() - timer) > TIMER_DELAY) && ledStatus == true)
  { 
    timer = millis();

    analogWrite(SMOOTH_LED, pwmValue);
    pwmValue--;

    pwmValue == 0 ? ledStatus = false: ledStatus = true;
  }
```


