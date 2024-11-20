const { SerialPort } = require('serialport')
const { ReadlineParser } = require('@serialport/parser-readline');

const mqtt = require('mqtt');

var options = {
    host: '033fa3cafe6d4c7e889dcaa188b47350.s1.eu.hivemq.cloud',
    port: 8883,
    protocol: 'mqtts',
    username: 'trena',
    password: 'Trena123'
}

// initialize the MQTT client
var client = mqtt.connect(options);

client.on('connect', function () {
    console.log('Connected');
});

client.on('error', function (error) {
    console.log(error);
});

SerialPort.list().then((res) => {
    if (res.length == 0) {
        console.log('Sem portas conectadas');
        return;
    }
    res.forEach(port => {
        if (port.path == 'COM3') {
            initPort();
        } else {
            console.log('Sem arduino conectado');
        }
    });
}).catch((err) => {
    console.log(err);
})

function initPort() {
    //Cria a conexão com a porta COM3 (Falta fazer uma validação para ver se a porta existe)
    const port = new SerialPort({ 
        path: 'COM3',
        baudRate: 9600 ,
    })

    const parser = port.pipe(new ReadlineParser({ delimiter: '\r\n' }))

    port.on('open', () => {
        console.log("Aberta");
    })

    port.on('error', (err) => {
        console.log(${err});
    })

    //Quando a porta COM3 mandar algum dado
    parser.on('data', (dados) => {
        client.publish('topic/trena', Distância: ${dados.toString('utf8').split('.')[0]}cm);
    })

    parser.on('error', (err) => {
        console.log(${err});
    })
}