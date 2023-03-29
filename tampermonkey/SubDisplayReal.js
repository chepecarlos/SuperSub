// ==UserScript==
// @name         SubDisplayReal
// @namespace    http://tampermonkey.net/
// @version      0.2
// @description  Enviar Sub de Youtube por MQTT
// @author       ChepeCarlos
// @match        *://studio.youtube.com/*
// @icon         https://www.google.com/s2/favicons?sz=64&domain=tampermonkey.net
// @grant        none
// @require      https://cdnjs.cloudflare.com/ajax/libs/mqtt/4.3.7/mqtt.min.js
// @run-at document-end
// ==/UserScript==

const config = {
    brokerMQTT: "wss://test.mosquitto.org:8081/mqtts",
    topic: "alsw/subreal"
};

let client = mqtt.connect(config.brokerMQTT);

function EventoConectar() {
    console.log("Conectado MQTT");

}

function EventoReconectar(){
    console.log("Reconectando MQTT");
}

function EventoDesconectar(){
    console.log("Desconectar MQTT");
}

client.on("connect", EventoConectar);
client.on("reconnect", EventoReconectar);
client.on("disconnect", EventoDesconectar);

(function() {
    'use strict';

    var obtenerSub = function(){
        let subReal = document.getElementsByClassName('metric-value-big style-scope ytcd-channel-facts-item');
        if (subReal.length <= 0) {
            subReal = document.getElementsByClassName('metric-value style-scope yta-latest-activity-card');
        }
        if (subReal.length <= 0) {
            return null;
        }
        return subReal[0].innerHTML.replace(',', '');
    }

    function enviarMQTT(subReal){
        if(client.connected){
            console.log("Enviando MQTT " + config.topic + "-" + subReal);
            client.publish(config.topic, subReal);
        }
    }

    function buscarSub(){
        let subReal = obtenerSub();
        if(subReal != null){
            enviarMQTT(subReal);
        }
    }

    setInterval(() =>{
        let subReal = obtenerSub();
        if(subReal != null){
            enviarMQTT(subReal);
        }
    }, 10000);
})();

