async function requisicao() {
  event.preventDefault();
    const brand =
    document.getElementById('marca').value;
    const product_type =
    document.getElementById('product_type').value;
    const categories =
    document.getElementById('a').value;
    const tags =
    document.getElementById('b').value;
    const price_greater_than =
    document.getElementById('price').value;
  
   

if (product_type !== '' || brand !== '' || categories  !== '' || tags  !== '' || price_greater_than !== '') {
    var response = await fetch(`http://makeup-api.herokuapp.com/api/v1/products.json?product_type=${product_type}&brand=${brand}&categories=${categories}&tags=${tags}&price_greater_than=${price_greater_than}`)

    var produtos = await response.json();

    var elementoLista = document.getElementById('listaProdutos');

    elementoLista.innerHTML = '';


    for (let i = 0; i < produtos.length; i++) {
      elementoLista.innerHTML += `
    <div class="cardProduto">
      <img src="${produtos[i].image_link}" />
      <p>${produtos[i].name}</p>
      <p>${produtos[i].price}</p>
    </div>
  `;
    }
  }
}
