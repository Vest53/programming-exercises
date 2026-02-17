const product_types = [
    {
        name: 'Blush',
        categories: [
            'Powder',
            'Cream'
        ],
        tags: [
            'Vegan',
            'Gluten free',
            'Canadian',
            'Natural',
            'Non-gmo',
            'Purpicks',
            'Usda organic',
            'Organic',
            'Certclean',
            'Ewg verified',
            'Hypoallergenic',
            'No talc',
        ]
    },

    {
        name: 'Bronzer',
        categories: [
            'Powder',
        ],
        tags: [
            'Gluten free',
            'Canadian',
            'Natural',
            'Organic',
            'Vegan',
            'Purpicks',
            'Ewg verified',

        ]
    },
    {
        name: 'Eyebrow',
        categories: [
            'Pencil',
        ],
        tags: [
            'Purpicks',
            'Ewg verified',

        ]
    },
    {
        name: 'Eyeliner',
        categories: [
            'Pencil',
            'Liquid',
            'Gel',
            'Cream',
        ],
        tags: [

            'Vegan',
            'Gluten free',
            'Canadian',
            'Natural',
            'Certclean',
            'Purpicks',
            'Ecocert',
            'Organic',
            'Certclean',
            'Ewg verified',
            'Hypoallergenic',
            'No talc',
        ]
    },
    {
        name: 'Eyeshadow',
        categories: [
            'Pencil',
            'Palette',
            'Cream',
        ],
        tags: [

            'Vegan',
            'Canadian',
            'Natural',
            'Gluten free',
            'Non-gmo',
            'Purpicks',
            'Certclean',
            'Ewg verified',
            'Organic',
            'Usda organic',
            'Hypoallergenic',
            'No talc',
            'Ecocert',
        ]
    },
    {
        name: 'Foundation',
        categories: [
            'Concealer',
            'Liquid',
            'Contour',
            'Cream',
            'Bb cc',
            'Mineral',
            'Powder',
            'Highlighter',
        ],
        tags: [

            'Vegan',
            'Gluten free',
            'Canadian',
            'Natural',
            'Certclean',
            'Purpicks',
            'Ecocert',
            'Organic',
            'Certclean',
            'Ewg verified',
            'Hypoallergenic',
            'No talc',
        ]
    },
    {
        name: 'Lip liner',
        categories: [
            'Pencil',
        ],
        tags: [

            'Natural',
            'Vegan',
            'Gluten free',
            'Canadian',
            'Purpicks',
            'Ewg verified',
            'Hypoallergenic',
            'No talc',
            'Cruelty free',
        ]
    },
    {
        name: 'Lipstick',
        categories: [
            'Lipstick',
            'Lip gloss',
            'Liquid',
            'Lip stain',
        ],
        tags: [

            'Canadian',
            'Natural',
            'Gluten free',
            'Non-gmo',
            'Peanut free product',
            'Vegan',
            'Cruelty free',
            'Organic',
            'Purpicks',
            'Certclean',
            'Chemical free',
            'Ewg verified',
            'Hypoallergenic',
            'No talc',
        ]
    },
    {
        name: 'Mascara',
        categories: [

        ],
        tags: [

            'Natural',
            'Gluten free',
            'Vegan',
            'Canadian',
            'Organic',
            'Purpicks',
            'Ewg verified',
            'Hypoallergenic',
            'No talc',
            'Ecocert',
            'Usda organic',
            'Certclean',
        ]
    },
    {
        name: 'Nail polish',
        categories: [
        ],
        tags: [

            'Vegan',
            'Canadian',
            'Natural',
            'Gluten free',
            'Fair trade',
            'Sugar free',
            'Non-gmo',
            'Dairy free',
        ]
    },
]
const elemProductType = document.getElementById
    ('product_type');

for (let product_type of product_types) {
    const option = new Option(product_type.name);
    elemProductType.add(option);
}

function setCategories() {
    const tiposelecionado = document.getElementById
        ('product_type').value;
    for (let value of product_types) {
        if (value.name === tiposelecionado) {
            for (let category of value.categories) {
                const option = new Option(category);
                a.add(option);

            }
        }
    }
}
function setTags() {
    const tiposelecionado = document.getElementById
        ('product_type').value;
    for (let value of product_types) {
        if (value.name === tiposelecionado) {
            for (let tags of value.tags) {
                const option = new Option(tags);
                b.add(option);
            }
        }
    }

}