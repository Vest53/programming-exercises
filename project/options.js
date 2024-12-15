document.getElementById('save').addEventListener('click', () => {
    const interval = document.getElementById('interval').value;
    chrome.storage.sync.set({ notificationInterval: interval }, () => {
        alert('Intervalo salvo!');
    });
});

// Carregar o intervalo salvo quando a página for aberta
document.addEventListener('DOMContentLoaded', () => {
    chrome.storage.sync.get('notificationInterval', (data) => {
        document.getElementById('interval').value = data.notificationInterval || 30; // Padrão de 30 minutos
    });
});
