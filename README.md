# WEB_SC_BT1
Bài tập 01 của sinh viên: K225480106057 - Phạm Mạnh Quỳnh - môn An toàn và bảo mật thông tin
# BÀI TẬP 1: TÌM HIỂU CÁC PHƯƠNG PHÁP MÃ HOÁ CỔ ĐIỂN
- caesar
- affine
- hoán vị
- vigenere
- playfair
** Với mỗi phương pháp, hãy tìm hiểu:**
- Tên gọi
- Thuật toán mã hoá, thuật toán giải mã
- Không gian khóa
- Cách phá mã (mà không cần khoá)
- Cài đặt thuật toán mã hoá và giải mã bằng code C++ và bằng html+css+javascript
1. Caesar
- Tên gọi: Caesar cipher (mã của Julius Caesar): dịch vòng các chữ cái theo một dịch chuyển k (shift)
- Thuật toán:
  + Mã hóa: E(p) = (p + k) mod 26
  + Giải mã: D(c) = (c - k) mod 26
- Không gian khóa: 26 khả năng
- Cách phá (không cần khóa):
  + Brute force: thử 26 giá trị k.
  + Phân tích tần suất: so sánh tần suất chữ cái -> khớp E -> suy k.
- Kết quả mã hóa và giải mã ( hình ảnh):
  + HTML, JS, CSS
  + Mã hóa:
 <img width="1920" height="1080" alt="image" src="https://github.com/user-attachments/assets/354fb3b2-9d57-490a-b249-5ce34d6f8e91" />

  + Giải mã:
  <img width="1920" height="1080" alt="image" src="https://github.com/user-attachments/assets/5375a2d5-0717-4c9b-a6e0-3694e980f6e8" />
  + C++:
  + mã hóa:
 <img width="1036" height="304" alt="Screenshot 2025-09-28 201842" src="https://github.com/user-attachments/assets/0cd18c0a-7e30-47c2-8544-c9da1f267833" />

  + giải mã:
  <img width="1112" height="312" alt="image" src="https://github.com/user-attachments/assets/c7844f35-2aa4-4bc6-9207-321f93e67777" />

2. affine:
- Tên gọi: Affine cipher: biến đổi affine trên modular 26
- Thuật toán:
  + Mã hóa: E(p) = (a*p + b) mod 26
  + Giải mã: D(c) = a^{-1} * (c - b) mod 26
- Không gian mã hóa:
  + a có φ(26)=12 giá trị (1,3,5,7,9,11,15,17,19,21,23,25)
  + b có 26 giá trị → tổng 12*26 = 312 cặp (a,b).
- Cách phá (không cần khóa):
  + Brute force dùng 312 cặp.
  + Phân tích tần suất: với số lượng lớn văn bản, suy a,b bằng cách so khớp tần suất.
- Kết quả mã hóa và giải mã ( hình ảnh):
  + HTML, JS, CSS:
  + Mã hóa:
  <img width="920" height="698" alt="image" src="https://github.com/user-attachments/assets/b7dbf697-1add-4124-b2f3-291c46666ace" />

  + Giải mã:
<img width="880" height="634" alt="image" src="https://github.com/user-attachments/assets/76263e34-93b2-46fb-b1e9-7e47cf6cadc6" />
  + C++:
  + mã hóa:
  <img width="699" height="347" alt="image" src="https://github.com/user-attachments/assets/41d92dbe-aaaf-4a44-9611-2915a5df1550" />

  + giải mã:
  <img width="753" height="358" alt="image" src="https://github.com/user-attachments/assets/3422de86-38ec-4704-9591-77e80fceda5d" />
3. Hoán vị:
- Tên gọi: Permutation cipher (hoán vị chữ cái) — thường là monoalphabetic substitution defined by a permutation of alphabet
- Thuật toán:
  + Chuẩn bị một bảng ánh xạ 26 chữ cái → khóa là một hoán vị của A..Z.
  + Mã hóa: thay mỗi chữ cái p bằng mapping[p].
  + Giải mã: dùng mapping ngược.
- Không gian khóa: 26! (~4.03e26) — cực lớn.
- Cách phá (không cần khóa):
  + Phân tích tần suất: đây là phương pháp mạnh nhất để phá substitution monoalphabetic: dùng tần suất chữ cái, bigram/trigram, phân tích mẫu từ, known plaintext.
  + Hill-climbing / simulated annealing: thuật toán tối ưu hóa trên không gian hoán vị với hàm mục tiêu là độ tương đồng tần suất n-gram.
- Kết quả mã hóa và giải mã ( hình ảnh):
  + MHTL,CSS,JS:
  + mã hóa:
  <img width="993" height="726" alt="Screenshot 2025-09-28 202800" src="https://github.com/user-attachments/assets/c7db69d7-e085-4090-a27e-c7619295e6b7" />

  + giải mã:
<img width="745" height="549" alt="image" src="https://github.com/user-attachments/assets/a56b1544-5b06-4946-8c64-a1521882e668" />
  + C++:
  + mã hóa:
 
  + giải mã:
 
4. Playfair
- Tên gọi: Playfair cipher — mã hai chữ một (digraph cipher) dùng ma trận 5×5.
- Quy ước riêng của thuật toán PlayFair:
  + Thông thường gộp J vào I (hoặc bỏ Q) để được 25 chữ cái.
  + Chia văn bản thành cặp (digraph). Nếu một cặp có hai chữ cái giống nhau thì chèn ký tự filler (thường là X) giữa chúng. Nếu chữ lẻ thì padding X
- Thuật toán:
  + Xây ma trận 5×5 từ khóa (ghi các chữ khóa không lặp, rồi các chữ cái còn lại).
  + Với digraph (a,b):

  Nếu a và b cùng hàng → thay mỗi chữ bằng chữ bên phải tiếp theo (mã hóa) / trái (giải mã).
  Nếu cùng cột → thay bằng chữ bên dưới (mã hóa) / trên (giải mã).
  Nếu khác hàng/cột → thay bằng 2 chữ ở hàng tương ứng và cột giao nhau (hình chữ nhật): a -> (row_a, col_b), b -> (row_b, col_a).
- Không gian khóa: Ma trận 5×5 với 25 chữ cái → số khóa ~ 25! / (số cấu hình tương đương...) rất lớn.
- Cách phá (không cần khóa):
  + Phân tích digram (tần suất cặp chữ): Playfair làm thay đổi phân bố digram nên dùng phân tích digram + heuristics.
  + Hill-climbing: tối ưu ma trận khoá để tăng likelihood (cách tương tự substitution nhưng dùng digram).
  + Known plaintext attacks: nếu biết một phần plaintext, suy ma trận.
- Kết quả mã hóa và giải mã ( hình ảnh):
  + HTML, JS, CSS:
  + mã hóa:
  <img width="947" height="580" alt="image" src="https://github.com/user-attachments/assets/675b9819-8d24-43ee-8ce7-90368aad3c13" />

  + giải mã:
  <img width="909" height="570" alt="image" src="https://github.com/user-attachments/assets/ffc6e00d-ca75-44fa-ae6c-944a2c4964f9" />

  + C++
  + mã hóa:
  <img width="531" height="299" alt="image" src="https://github.com/user-attachments/assets/56a77e09-63f3-45bd-ad36-c9f9fbae93a9" />

  + giải mã:
  <img width="488" height="371" alt="image" src="https://github.com/user-attachments/assets/ea706ce8-109e-44f3-b27f-0191d9e43fae" />
5. Vigenere
- Tên gọi: Vigenere cipher — polyalphabetic substitution dùng khóa chữ.
- Thuật toán:
  + Khóa: chuỗi chữ cái K = k0 k1 ... k(m-1).
  + Mã hóa: E(p_i) = (p_i + k_{i mod m}) mod 26
  + Giải mã: D(c_i) = (c_i - k_{i mod m}) mod 26
- Không gian khóa: Nếu khóa dài m: 26^m. Nếu khóa có độ dài không biết, không gian lớn.
- Cách phá (không cần khóa):
  + Kasiski test: tìm khoảng cách giữa các mẫu lặp lại để ước lượng độ dài khóa m.
  + Friedman test: dùng chỉ số tương đồng để ước lượng m.
  + Khi biết m → phân chia văn bản thành m dãy, mỗi dãy là Caesar cipher → phá bằng phân tích tần suất / xác suất.
- Kết quả mã hóa và giải mã ( hình ảnh):
  + HTML, JS, CSS:
  + mã hóa:
  <img width="1917" height="505" alt="Screenshot 2025-09-28 204635" src="https://github.com/user-attachments/assets/975ae4e3-376b-4bb7-ae16-2cdfe3f5e16b" />

  + giải mã:
  <img width="1919" height="413" alt="image" src="https://github.com/user-attachments/assets/c0252bd2-ecb0-4316-ac39-b11d621fde15" />

  + C++
  + mã hóa:
  <img width="574" height="333" alt="image" src="https://github.com/user-attachments/assets/a61babb4-c2ee-4c9d-bbd5-6bd350684792" />

  + giải mã:
  <img width="593" height="302" alt="image" src="https://github.com/user-attachments/assets/13481693-0a41-475c-b817-8255e34266d2" />
