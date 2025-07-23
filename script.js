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
let verdeLigado = 0
let desligado = 0

function vermelhoOn() {
    if (verdeLigado == 1) {
        amareloOn()
        setTimeout(3000)
        Off()
        verdeLigado = 0
    }
    vermelho.classList.add("vermelho")
    //publish do topico
    const msg = new Paho.MQTT.Message("")
    msg.destinationName = "senai510/led/vermelho"
    clientWeb.send(msg)
}
function verdeOn() {
    verde.classList.add("verde")
    //publish do topico
    const msg = new Paho.MQTT.Message("")
    msg.destinationName = "senai510/led/verde"
    clientWeb.send(msg)
    verdeLigado = 1

}
function amareloOn() {
    Off()
    amarelo.classList.add("amarelo")
    //publish do topico
    const msg = new Paho.MQTT.Message("")
    msg.destinationName = "senai510/led/amarelo"
    clientWeb.send(msg)

}

function autoOn() {
    //publish do topico
    const msg = new Paho.MQTT.Message("")
    msg.destinationName = "senai510/led/automatico"
    clientWeb.send(msg)

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