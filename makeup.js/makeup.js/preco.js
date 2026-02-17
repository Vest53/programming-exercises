
 
    items.sort (async function preco() { (produtos) 
        event.preventDefault();
        const price =
        document.getElementById('price').value;

        var response = await fetch(`http://makeup-api.herokuapp.com/api/v1/products.json?product_type=${product_type}&brand=${brand}&categories=${categories}&tags=${tags}&price=${price}`)

         var produtos = await response.json();

      if (produtos.price > produtos.price) {
        return 1;
      }
      if (produtos.price < produtos.price) {
        return -1;
      }
      console.log(items)
      return 0;
    } );
  
