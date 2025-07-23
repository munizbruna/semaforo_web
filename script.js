//iot config
const clientId = "Esp32" + Math.floor(Math.random()*900) +90
let clientWeb = new Paho.MQTT.Client("broken.hivemq.com", 8884, clientId);
clientWeb.connected({
    useSSL:true, 
    onSucess: function(){
        alert("Conectado com sucesso!")
    },
    onFailure: function(){
        alert("A conexão falhou!")
    }
})

const verde = document.getElementById("verde")
const amarelo = document.getElementById("amarelo")
const vermelho = document.getElementById("vermelho")

function vermelhoOn() {
vermelho.classList.add("vermelho")
}
function verdeOn() {
verde.classList.add("verde")

}
function amareloOn() {
amarelo.classList.add("amarelo")
}

function autoOn() {

}
function Off() {
    vermelho.classList.remove("vermelho")
    verde.classList.remove("verde")
    amarelo.classList.remove("amarelo")

}