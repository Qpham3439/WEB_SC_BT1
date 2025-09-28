function permEncrypt() {
  let text = document.getElementById("permText").value;
  let key = document.getElementById("permKey").value.split(",").map(Number);
  let n = key.length;
  let res = "";

  for (let i = 0; i < text.length; i += n) {
    let block = text.substr(i, n).padEnd(n, "X");
    for (let k of key) res += block[k - 1] || "";
  }
  document.getElementById("permResult").innerText = res;
}

function permDecrypt() {
  let text = document.getElementById("permText").value;
  let key = document.getElementById("permKey").value.split(",").map(Number);
  let n = key.length;
  let res = "";

  for (let i = 0; i < text.length; i += n) {
    let block = text.substr(i, n);
    let arr = [];
    for (let j = 0; j < n; j++) arr[key[j] - 1] = block[j];
    res += arr.join("");
  }
  document.getElementById("permResult").innerText = res;
}
