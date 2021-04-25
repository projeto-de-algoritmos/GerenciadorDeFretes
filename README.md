# Gerenciador de Fretes

**Número da Lista**: X<br>
**Conteúdo da Disciplina**: Programação Dinâmica<br>

## Alunos
|Matrícula | Aluno |
| -- | -- |
| 16/0049733 |  Felipe Borges de Souza Chaves |
| 18/0055241 |  Victor Jorge da Silva Gonçalves |

## Sobre 
Este projeto consiste em um mini sistema gerenciador de fretes para desktop. O proposito desse sistema é poupar o usuário do intenso trabalho de análise e cálculos para maximizar seu lucro diante de uma demanda de serviços de frete. O sistema aceita diversos parâmetros a serem considerados relevantes na tomada de decisão, tais como: número de funcionários disponíveis para um determinado período, número de veículos disponíveis, horário dos serviços requisitados e a rentabilidade da realização de cada serviço.

Para fornecer um ambiente controlado para testes, fornecemos um gerador de demandas fictícias e aleatórias, onde o usuário pode verificar a sugestão dada pelo sistema e verificar se está de acordo.

## Screenshots
Adicione 3 ou mais screenshots do projeto em funcionamento.

## Instalação 

**Linguagem**: C++<br>
**Biblioteca**: SDL 2.0<br>

> Em caso de não portabilidade, entre em contato com a dupla!

### Ubuntu ou Debian

Para efetuar a instalação das dependências, execute os comandos:

```bash
sudo apt-get install g++
```
```bash
sudo apt-get install make
```
```bash
sudo apt-get install libsdl2-dev
```
```bash
sudo apt-get install libsdl2-image-dev
```
```bash
sudo apt-get install libsdl2-ttf-dev
```

### Windows

Infelizmente, o código deste projeto utiliza de cabeçalhos e esquemas de compilação que não são portáveis para Windows. Sendo assim, para a correta execução do código recomendamos a instalação do [WSL 1](https://docs.microsoft.com/pt-br/windows/wsl/install-win10), do [VcXsrv](https://sourceforge.net/projects/vcxsrv/) e do [Ubuntu 18.04](https://www.microsoft.com/en-us/p/ubuntu-1804-lts/9n9tngvndl3q?activetab=pivot:overviewtab) sobre o WSL1. Feita a instalação desses componentes, execute dentro do bash do Ubuntu os mesmos passos listados para [Ubuntu ou Debian](#ubuntu-ou-debian).

### MacOS

Para instalar o SDL no MacOS, recomendamos o uso do [_homebew_](https://brew.sh/index_pt-br).

No terminal, execute:

```bash
brew install make
```

```bash
brew install sdl2
```

```bash
brew install sdl2_ttf
```

```bash
brew install sdl2_image
```

## Uso

> Para usuários ***Windows*** com WSL1 e Ubuntu, será necessário executar previamente o VcXsrv no desktop do Windows e em seguida executar no bash do Ubuntu o seguinte comando:
>
> ```bash
> export DISPLAY=:0
> ```

A execução da aplicação é simples e pode ser feita executando comando abaixo a partir do diretório 2DCollisionDetection.

```bash
make && make run
```
