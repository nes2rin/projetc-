console.log(document)
var buttons = document.querySelectorAll("button")
console.log(buttons);
let like_buttons= document.querySelectorAll('.like')
var total=document.getElementById('total')
var prices= document.querySelectorAll('.price')
var delete_btns = document.querySelectorAll('.delete')
// var p= document.querySelectorAll("p");
// var value = Number(p.innerHTML) ;
function equation (e){
    var cible = e.target
    var c = cible
    var div = c.parentElement
    console.log(div)
    console.log(c)
    var p = div.querySelector('p')
    var value = Number(p.innerHTML)
    console.log(value)
    if (c.innerHTML== "+")
    {value++}
    else if (c.innerHTML=="-" && value>0  ) { 
        {value--}
    }
    p.innerHTML=value
    var tr = div.parentElement.parentElement
    console.log(tr)
    var unit_price= tr.querySelector('.unitPrice')
    var up = Number(unit_price.innerHTML)
    var price = tr.querySelector('.price')
    price.innerHTML= up*value 
    sum()
}
for (let i=0;i<buttons.length;i++){
    buttons[i].addEventListener('click',equation)
}
function changeColor(e) {  
    var cible=e.target
    if(cible.style.color!=="red"){
        cible.style.color='red'
    }else cible.style.color=''
}
for (let i = 0; i < like_buttons.length; i++) {
    like_buttons[i].addEventListener('click',changeColor);
    
}
function sum() {
    var somme = 0

    for (let i = 0; i < prices.length; i++) {
        somme+=Number(prices[i].innerHTML)
        
    }
    total.innerHTML =somme
function deleteRow(e){
var cible =e.target
var tr= cible.parentElement.parentElement.parentElement.parentElement
tr.remove()
}  
for (let i = 0; i < delete_btns.length; i++) {
    delete_btns[i].addEventListener('click',deleteRow )
}
}