# Transfeiror-Arduino
Três códigos salvos para uma apresentação de eletrônica (amanhã -- vish!) de um transferidor interativo, com um servomotor que move uma seta do transferidor, um potenciômetro que a controla, e três botões. Um botão que muda a seta para o ângulo de 30°, um para 45° e um para 60°.

Estes códigos não são garantidos, ainda, nem de funcionar. E não me responsabilizo por nenhum dano por uso qualquer deste código. Você que se vire!

# Códigos

- O código mais simples ("transferidor_sem_botoes") apenas gira a seta conforme o potenciômetro gira.
- O código principal ("transferidor") também o faz, mas ainda move a seta para um ângulo certo segundo o botão pressionado, com ordem de preferência; aos botões serem soltos, a seta volta ao ângulo de antes, então, voltando controle ao potenciômetro.
- O código mais complicado ("transferidor_boa_memoria") move a seta e mantém memória de todos os botões sendo pressionados, vendo que podem ser todos pressionados ao mesmo tempo, dando preferência ao último apertado. Se nenhum estiver mais apertado, o mesmo do código acima acontece: a seta volta ao ângulo que estava antes de os botões serem pressionados, e, depois, volta controle ao potenciômetro.
