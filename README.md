# ArousedShop

O que falta:
- Automatizar a contagem de produtos.
- Colocar barreira que verifica que o produto vendido no cadastro de venda realmente existe.
- Verificar erros abaixo.

Por alguma razão, a verificação de ativados de produtos duplica a mensagem que encontrou um produto desativada.

Por outra razão, a verificação de ativados de produtos não avisa quando tem um produto desativado que não seja o primeiro, mas envia a informação correta mesmo assim e o próximo cadastro de produto sobreescreve o desativado.