var buttons = document.querySelectorAll("button");
console.log(buttons);
var p= document.querySelector("p");
var value = Number(p.innerHTML) ;
function equation (e){
var cible = e.target;
var c = cible;
console.log(c.innerHTML);
if (c.innerHTML== "+")
{value++}
else if (c.innerHTML=="-"  ) { 

{value--}
}
p.innerHTML=value
}
for (let i=0;i<buttons.length;i++){
    buttons[i].addEventListener('click',equation)
}

