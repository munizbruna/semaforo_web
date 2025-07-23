//iot config
let clientWeb = null
const clientId = "Esp32" + Math.floor(Math.random() * 900) + 100
clientWeb = new Paho.MQTT.Client("broker.emqx.io", 8084, clientId);
clientWeb.connect({
    timeout: 5,
    useSSL: true,
    onSuccess: function () {
        alert("Conectado com sucesso!")
    },
    onFailure: function () {
        alert("A conexão falhou!")
    }
})

const verde = document.getElementById("verde")
const amarelo = document.getElementById("amarelo")
const vermelho = document.getElementById("vermelho")
const display = document.getElementById("display")

function vermelhoOn() {
    vermelho.classList.add("vermelho")
    //publish do topico
    const msg = new Paho.MQTT.Message("")
    msg.destinationName = "senai510/led/vermelho"
    clientWeb.send(msg)
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
    //publish do topico
    const msg = new Paho.MQTT.Message("")
    msg.destinationName = "senai510/led/desligar"
    clientWeb.send(msg)

}