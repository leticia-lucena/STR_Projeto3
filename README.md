# STR_Projeto3

# Simulação de cruzamento de trilhos de trem

## Descrição do Projeto
O projeto tem como objetivo desenvolver um sistema que simule a interação entre uma linha ferroviária e uma estrada, criando um ambiente onde trens e carros se encontram em um cruzamento. Tanto os trens quanto os carros podem se aproximar do cruzamento de qualquer direção e, para evitar acidentes, é necessário fechar a cancela sempre que um trem se aproxima do cruzamento, garantindo que os veículos parem. A sincronização eficiente do acesso ao cruzamento é essencial para o bom fucncionamento do modelo e será implementada utilizando semáforos, aplicando os princípios de sincronização e exclusão mútua.

## Requisitos
- Modelagem dos Trens e Carros: trens e carros são gerados nessa aplicação de acordo com variáveis estabelecidas no código. Carros trafegar no sentido norte-sul ou sul-norte, enquanto os trens podem viajar leste-oeste e oeste-leste. Não há mais de um trem no cruzamento seguindo na mesma direção simultaneamente, tendo em vista que isso se configura como uma impossibilidade prática para o problema.

- Cruzamento: caracteriza-se como um recurso compartilhado por carros e trens, cujo acesso é controlado por semáforos. É importante observar que dois trens podem cruzar simultaneamente se estiverem viajando em direções opostas. Os carros só terão permissão para cruzar se a cancela estiver levantada e a passagem do trem terá sempre prioridade.

- Semáforos: são utilizados para gerenciar o acesso ao cruzamento, evitando condições de corrida e deadlocks. Eles garantirão uma passagem segura e eficiente através do cruzamento, controlando o fluxo de trens e carros.

- Interface com o Usuário: a comunicação entre o sistema e os usuários é feita por meio de mensagens que indicam o estado atual dos trens e carros (aproximando-se, cruzando e cruzado) e a situação atual do cruzamento.

## Demonstração
O vídeo de demonstração do projeto pode ser encontrado no link: 
