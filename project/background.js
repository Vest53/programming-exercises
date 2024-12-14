let totalTime = 0;
let timer;

function startTimer() {
    timer = setInterval(() => {
        totalTime += 1; // Incrementa o tempo em segundos
        if (totalTime % 3600 === 0) { // A cada 1 hora
            sendNotification();
        }
    }, 1000);
}

function sendNotification() {
    chrome.notifications.create({
        type: "basic",
        iconUrl: "icon.png",
        title: "Hora de uma pausa!",
        message: "Você está navegando há 30 minutos. Lembre-se de descansar!",
        priority: 2
    });
}

// Inicia o timer quando a extensão é ativada
chrome.runtime.onInstalled.addListener(startTimer);
chrome.tabs.onActivated.addListener(() => {
    if (!timer) {
        startTimer();
    }
});
