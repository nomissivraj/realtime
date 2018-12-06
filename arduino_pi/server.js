var SerialPort = require('serialport')
var Readline = SerialPort.parsers.Readline

var serialPort = new SerialPort('/dev/ttyACM0', {
  baudRate: 9600
})

var parser = new Readline()
serialPort.pipe(parser)
parser.on('data', function (data) {
  console.log('data received: ' + data)
})

serialPort.on('open', function () {
  console.log('Communication is on!')
})
