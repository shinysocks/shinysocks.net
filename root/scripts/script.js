function hover(id, image) {
    let icon = document.getElementById(id)
    icon.setAttribute('src', image)
}
  
function unhover(id, image) {
    let icon = document.getElementById(id)
    icon.setAttribute('src', image)
}

function random_color(element) {
    const colors = ["#b4befe", "#f5c2e7", "#cba6f7", "#f38ba8", "#fab387", "#f9e2af", "#a6e3a1", "#89dceb", "#89b4fa", "#b4befe", "#ffffff" ]
    let randnum = Math.floor(Math.random() * 10)
    element.style.color = colors[randnum];
}
