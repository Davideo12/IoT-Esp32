const path = require('path');
const socketIo = require('socket.io');
const axios = require('axios');
const express = require('express');
const app = express();

url = 'http://192.168.1.72'

app.use(express.static(path.join(__dirname, '/public')));

const server = app.listen(4000, () => {
    console.log('Servidor online...');
});

const io = socketIo.listen(server);

io.on('connection', socket => {
    console.log('Usuario conectado...');
    io.emit('ready', {state: 'ready'});
    socket.on('on', data => {
        axios.get(url + '/H')
        .then(res => console.log(res))
        .catch(err => console.log(err))
    })

    socket.on('off', data => {
        axios.get(url + '/L')
        .then(res => console.log(res))
        .catch(err => console.log(err))
    })
})