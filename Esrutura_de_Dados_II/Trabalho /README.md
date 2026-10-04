INSTITUTO FEDERAL DE EDUCAÇÃO, CIÊNCIA E TECNOLOGIA DO PIAUÍ
**CAMPUS PARNAÍBA** **CURSO ANÁLISE E DESENVOLVIMENTO DE SISTEMAS**
# **TRABALHO AVALIATIVO - ESTRUTURA DE DADOS** **Árvore Radix/Patricia**

### **Autores:**
* ANTONIO MARCOS OLIVEIRA DA SILVA
* ARTHUR CÉSAR CARVALHO CASTRO
* DIOGO GABRIEL GONÇALVES DE SOUZA
* IAGO SILVA DE CARVALHO
* JOSÉ CLAUDIO ARAUJO LIMA SOTERO
* KAYO PEREIRA SILVA
* ROGER BRITO DA SILVA

PARNAÍBA, 2026

---
1 INTRODUÇÃO AO PROBLEMA

O problema proposto e que será trabalhado no material deste documento se refere ao tema do projeto 2: "O Roteador de Núcleo e Casamento de Prefixos". O enunciado do problema trás o cenário de qual estrutura deve ser utilizada para a criação de uma tabela de rotas de pacotes no roteador, toda vez que o roteador recebe um pacote ele deve consultar a tabela de rotas para saber para onde deve enviá-lo.

As especificações e restrições técnicas são:

1. As tabelas de rotas na internet usam a regra LPM (Longest Prefix Match). Ao receber um pacote, o roteador verifica o IP de destino e na lista de rotas, escolhe o IP que possui o maior prefixo igual ao IP de destino (com mais bits em comum à esquerda);


2. Tabelas Hash falham, pois apesar de ter um tempo $O(1)$, procuram por prefixos exatos (Exact Match), e uma BTS (Binary Tree Search) e Árvore AVL (nomeada com base nos seus idealizadores, Adelson-Velsky e Landis, também conhecida como árvore binária auto balanceada) foi feita para buscar um dado inteiro, não sendo possível (por padrão) buscar prefixos. Ambos casos violam as restrições de tempo do hardware;


3. A estrutura deve ter uma memória otimizada e volátil, de forma que, prefixos idênticos não ocupem um espaço maior que seu tamanho.

2 SOLUÇÃO

Ao buscar por uma possível solução ao problema, a primeira estrutura que se é achado que é capaz de buscar por prefixos com LPM é uma conhecida por Árvore Trie. Essa árvore, à primeira vista, seria capaz de solucionar o problema proposto, contudo, ela possui uma falha grave que vai contra uma das restrições. Se um IP possuir um prefixo longo (suponhamos que sejam oito bits de 1) a árvore criaria 8 nós diferentes para armazenar cada um dos bits com valores repetidos, assim, quebrando a terceira restrição.

Para solucionar o problema da Trie, foi desenvolvido a Árvore Radix, também conhecida como Trie compactada ou Árvore Patricia. Esta árvore é capaz de compactar os nós que possuem apenas um filho, e que este filho não possui nenhuma ramificação. Utilizando o exemplo anterior, teríamos apenas um nó com uma string que guardaria os 8 bits de 1.

2.1 O ALGORITMO

Podemos separar o algoritmo da Árvore Trie em 3 funções básicas: A busca, a inserção e a remoção. A busca consiste em caminhar pelos nós comparando o prefixo buscado com as strings armazenadas em cada nó.

A inserção precisa decidir se vai apenas criar um novo nó ou se vai partir um nó existente no meio (uma operação chamada split).  Quando uma palavra é inserida, o algoritmo percorre a árvore combinando os prefixos. Três cenários podem ocorrer:

1. O algoritmo chega em um ponto onde não há nó que compartilhe letras com o restante da string, então é criado um novo nó com o restante da string;

2. A string inserida termina exatamente onde um nó existente termina, então, este nó é marcado como "fim de uma palavra";

3. O algoritmo nota que a string e o nó compartilham apenas um pedaço do prefixo antes de se dividirem, então é realizada a operação de split. O algoritmo separa os prefixos dos sufixos, o sufixo da palavra original fica à esquerda, enquanto o da palavra que está sendo inserida vai à direita.

A remoção realiza o inverso da inserção. Ela tem a responsabilidade de limpar a árvore preservando as suas propriedades. Isso envolve uma operação chamada merge. Ao remover uma palavra:

1. O algoritmo localiza o nó da palavra usando a lógica de busca;

2. Ele remove a marcação de "fim de uma palavra";

3. Se este nó não é fim de palavra, ele é um nó que não possui filhos, ele então é removido;

4. Após a remoção, o algoritmo verifica o "Nó pai". Se o pai ficou com apenas um filho restante, as regras da Radix foram violadas;

5. O algoritmo então concatena a chave do pai com a chave do nó filho restante.



3 COMPLEXIDADE DA ESTRUTURA

As complexidades de tempo e espaço da Árvore Radix, são similares às da Trie, mas trazem otimização no uso prático de memória e comportamento de hardware. Considerando as seguintes variáveis:

* **N:** A quantidade de chaves (nós) armazenadas na árvore;

* **W:** Comprimento máximo de uma chave(string);

* **M:** Tamanho do alfabeto.

3.1 COMPLEXIDADE DE TEMPO

Tanto a Árvore Radix quanto a Trie, a complexidade de tempo, em inserções e buscas, não é a $O(N)$, mas sim o tamanho máximo da chave, logo a complexidade é $O(W)$. No pior caso, terei que realizar W comparações para achar o prefixo desejado. Embora a complexidade seja a mesma entre as duas árvores, devido a forma em que a Radix é implementada, agrupando os caracteres na memória, a busca se torna mais rápida, evitando muitos erros de cache.

É importante destacar que, ao realizar a sua busca de M em uma Radix, dependendo da forma que a árvore armazena as suas chaves a complexidade de tempo pode mudar:

* Para arrays indexados, a complexidade permanece $O(W)$.

* Para listas encadeadas ou tabelas hash, a complexidade aumenta para $O(W^{*}logM)$.

3.2 COMPLEXIDADE DE ESPAÇO

O tamanho do espaço é representado pela letra N, sendo ele a soma de todos os prefixos após a compreensão deles em nós menores, devido a propriedade de criar nós apenas quando há ramificações, se houver strings muito longas que não se ramificam o custo de espaço cai para $O(1)$ para aquela string.

Em seu pior caso, onde nenhuma palavra compartilha nenhuma letra ou prefixo com outra, a complexidade aumenta para $O(N^{*}W^{*}M)$.

4 REFERÊNCIAS

* CDHISTORY. Patricia Árvore ou Trie, Árvore Radix, Árvore crit-bit. **CDHistory**, 2026. Disponível em: [https://cdhistory.org/pt/patricia-%c3%81rvore-ou-trie-%c3%alrvore-radix-%c3%alrvore-crit-bit/](https://www.google.com/search?q=https://cdhistory.org/pt/patricia-%25c3%2581rvore-ou-trie-%25c3%25alrvore-radix-%25c3%25alrvore-crit-bit/).  Acesso em: 23 jun. 2026.

* FEOFILOFF, Paulo. Tries e árvores digitais. São Paulo: IME-USP, 2026.  Disponível em: [https://www.ime.usp.br/~pf/estruturas-de-dados/aulas/tries.html](https://www.ime.usp.br/~pf/estruturas-de-dados/aulas/tries.html). Acesso em: 24 jun. 2026.

* LINKEDIN. O que distingue uma árvore Trie de uma árvore Radix? **LinkedIn Advice**, 2026. Disponível em: [https://www.linkedin.com/advice/1/what-distinguishes-trie-from-radix-tree-skills-programming-kamdc?lang=pt&lang=pt&originalSubdomain=pt&lipi=urn%3Ali%3Apage%3Ad_flagship3_pulse_read%3BkyYeAclCR4mn60%2BaoX5syg%3D%3D&originalSubdomain_pt](https://www.google.com/search?q=https://www.linkedin.com/advice/1/what-distinguishes-trie-from-radix-tree-skills-programming-kamdc%3Flang%3Dpt%26lang%3Dpt%26originalSubdomain%3Dpt%26lipi%3Durn%253Ali%253Apage%253Ad_flagship3_pulse_read%253BkyYeAclCR4mn60%252BaoX5syg%253D%253D%26originalSubdomain_pt).  Acesso em: 23 jun. 2026.

* MOLENAAR, Rene. Longest Prefix Match Routing. **
* 
* NetworkLessons**, 2026.  Disponível em: [https://networklessons.com/ip-routing/longest-prefix-match-routing](https://networklessons.com/ip-routing/longest-prefix-match-routing). Acesso em: 24 jun. 2026.