# Projeto-ICC
Desenvolvendo o jogo "Naruto: ultimate ninja fighter"

Aqui vai alguns links uteis:
<ul>
  <li>Link explicativo sobre git: http://rogerdudler.github.io/git-guide</li>
  <li>Minitutorial pratico (nao gostei muito): http://rogerdudler.github.io/git-guide</li>
  <li>Videoaula (melhor coisa): https://www.youtube.com/playlist?list=PLInBAd9OZCzzHBJjLFZzRl6DgUmOeG3H0</li>
  <li>Explicação boa que eu <strike>peguei de um processo seletivo de um grupo de extensão da poli</strike> encontrei na net: https://github.com/ThundeRatz/Bixos-2018/blob/master/git/README.md
</ul>

Para começar, esse repositório está privado, então não tem problema usarmos material com direitos autorais. Além disso, a única maneira de fazer isso acontecer é <b>tornar vocês colaboradores do projeto</b>.Isso é legal, pois vocês têm controle quase total do repositório(so nao podem deletar eu acho) <b>MAS</b>, pra evitar problemas, quero estabelecer duas regras entre nos:
<ul>
  <li><h3>Somente realizar "merge", ou seja, <b>criar pull requests</b> pela plataforma do github</h3><li>Pois é possivel fazer tudo via código, mas dessa maneira ninguem vê nada, é tudo automático</li></li>
  <li><h3>Somente realizar "merge", ou seja, <b>aprovar pull request</b>, com a aprovação dos outros dois membros</h3></li>
</ul>

Provavelmente vocês ainda nao entendem disso, mas nada que uma tarde de videoaulas e eu pra ajudar não resolva. Então, seguindo esse ritimo, vamos esperar a aprovação dos outros membros para dar push

<h4> Atenção </h4><br>
PS: Há outro jeito de fazer "merge" sem usar merge, que é, basicamente, selecionar a branch master (por exemplo) e, a partir desta, realizar um "pull" de outra branch: exemplo
  <br><code>git checkout master //seleciona a branch master</code><br>
  <br><code>git pull origin fixando_arquivo //puxa todo o conteudo da branch fixando_arquivo e da um "merge" na branch master</code><br>
Esse processo não é algo essencialmente ruim. Por exemplo, se eu tenho uma branch "salvar-cadastros", mas eu preciso implementar as fotos dos ninjas, eu crio uma branch "foto_ninja", eu posso copiar o conteudo da minha branch "salvar-cadastros" para esssa que acabei de criar, pois assim todo meu progresso estará nesta nova. Para fazer isso, eu faço: 
    <br><code>git checkout salvar-cadstros //seleciona a branch salvar-cadastros</code><br>
    <br><code>git checkout -b foto_ninja //(-b cria) e seleciona a branch foto_ninja, utilizando como base a atual branch</code> <b>(por padrão, sempre que você cria uma nova branch, você a cria como clone da branch atual)</b><br>
    
Mesmo sendo algo neutro, tomem cuidado ao relizar esses dois processos acima. Apesar de que sempre podemos voltar à versões anteriores, todo cuidado é pouco
 
<br>VALEU GALERINHA
  
