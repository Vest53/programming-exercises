document.addEventListener('DOMContentLoaded', () => {
    chrome.runtime.getBackgroundPage((backgroundPage) => {
        setInterval(() => {
            document.getElementById('timeSpent').innerText = `Tempo total navegando: ${backgroundPage.totalTime} segundos`;
        }, 1000);
    });
});
