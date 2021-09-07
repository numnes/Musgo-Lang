                                 __  __                       _
                                |  \/  |_   _ ___  __ _  ___ | |    __ _ _ __   __ _
                                | |\/| | | | / __|/ _` |/ _ \| |   / _` | '_ \ / _` |
                                | |  | | |_| \__ \ (_| | (_) | |__| (_| | | | | (_| |
                                |_|  |_|\__,_|___/\__, |\___/|_____\__,_|_| |_|\__, |
                                                  |___/                        |___/

Musgo_lang é uma linguagem criada para disciplina de compiladores no curso de Ciência da Computação da Unioeste. É fortemente tipada e estática, imperativa. Tem sua sintaxe inspirada em C/C++ e Rust.

Mais detalher sobre a linguagem podem ser encontrados na [neste documento](https://github.com/matheusnunesismael/musgo-lang/blob/main/doc.md) de especificação.
<br/>

#### Compilação do compilador

O compilador da linguagem foi escrito em C++. A geração do executável do compilador pode ser feita rápidamente, utilizando o CMake será gerado o arquino Makefile mais adequado para seu sistema, assim basta acessar a pasta raiz do repositório e executar:

```
$# cmake .
```

Com o arquivo Makefile gerado basta executar o make para gerar o executável:

```
$# make
```

Assim o executável do compilador chamado MUSGO será gerado.
<br/>

#### Utilização

Para compilar um código em Musgo basta executar o compilador passando o caminho para o script a ser compilado, este repositório possúi dois arquivos de exemplo na pasta data.

```
$# ./MUSGO data/main.mg
```

## Mais instruções serão adicionadas aqui futuramente

### Contrubuidores

<p align="center">
  <table>
    <tr>
      <td align="center">
        <a href="https://github.com/matheusnunesismael">
          <img src="https://avatars.githubusercontent.com/u/32654785?v=4?s=100" width="100px;" alt=""/>
          <br/>
          <sub>
            <b>Matheus Nunes</b>
          </sub>
        </a>
        <br/>
        <a href="https://github.com/matheusnunesismael/actions-template-sync/commits?author=matheusnunesismael" title="Documentation">📖</a> 
        <a href="https://github.com/matheusnunesismael/actions-template-sync/commits?author=matheusnunesismael" title="Code">💻</a>
      </td>
      <td align="center">
        <a href="https://github.com/mateusedival">
          <img src="https://avatars.githubusercontent.com/u/28989384?v=4?s=100" width="100px;" alt=""/>
          <br/>
          <sub>
            <b>Mateus Edival</b>
          </sub>
        </a>
        <br/>
        <a href="https://github.com/matheusnunesismael/Musgo-Lang/commits?author=mateusedival" title="Documentation">📖</a> 
        <a href="https://github.com/matheusnunesismael/Musgo-Lang/commits?author=mateusedival" title="Code">💻</a>
      </td>
    </tr>
  </table>
</p>
