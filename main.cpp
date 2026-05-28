#include <iostream>
#include <queue>
#include <vector>
#include <string>
using namespace std;

struct LogNode {
    string kota;
    LogNode* next;
};

struct Paket {
    string resi;
    string asal;
    string tujuan;
    LogNode* histori;
};

class QueueHub {
    queue<Paket*> antrean;
public:
    void enqueue(Paket* p) { antrean.push(p); }
    Paket* dequeue() {
        if (antrean.empty()) return nullptr;
        Paket* p = antrean.front();
        antrean.pop();
        return p;
    }
    bool isEmpty() { return antrean.empty(); }
};

void tambahHistori(Paket* p, string kota) {
    LogNode* logBaru = new LogNode{kota, nullptr};
    LogNode* temp = p->histori;
    while (temp->next) temp = temp->next;
    temp->next = logBaru;
}

void lacakResi(Paket* p) {
    cout << "Histori paket " << p->resi << ":\n";
    LogNode* temp = p->histori;
    while (temp) {
        cout << "-> " << temp->kota << "\n";
        temp = temp->next;
    }
}

int main() {
    QueueHub jakarta, bandung, sumedang;
    vector<Paket*> daftarPaket;

    int pilihan;
    do {
        cout << "\n=== MENU SIMULASI LOGISTIK ===\n";
        cout << "1. Registrasi Paket\n";
        cout << "2. Dispatch Paket Jakarta -> Bandung\n";
        cout << "3. Dispatch Paket Bandung -> Sumedang\n";
        cout << "4. Lacak Resi\n";
        cout << "0. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilihan;

        if (pilihan == 1) {
            string resi, asal, tujuan;
            cout << "Masukkan Nomor Resi: "; cin >> resi;
            cout << "Kota Asal: "; cin >> asal;
            cout << "Kota Tujuan: "; cin >> tujuan;

            Paket* p = new Paket{resi, asal, tujuan, nullptr};
            if (asal == "Jakarta") jakarta.enqueue(p);
            else if (asal == "Bandung") bandung.enqueue(p);
            else if (asal == "Sumedang") sumedang.enqueue(p);

            p->histori = new LogNode{asal, nullptr};
            daftarPaket.push_back(p);

            cout << "Paket " << resi << " berhasil diregistrasi.\n";
        }
        else if (pilihan == 2) {
            Paket* p = jakarta.dequeue();
            if (p) {
                bandung.enqueue(p);
                tambahHistori(p, "Bandung");
                cout << "Paket " << p->resi << " dipindahkan ke Bandung.\n";
            } else cout << "Tidak ada paket di Jakarta.\n";
        }
        else if (pilihan == 3) {
            Paket* p = bandung.dequeue();
            if (p) {
                sumedang.enqueue(p);
                tambahHistori(p, "Sumedang");
                cout << "Paket " << p->resi << " dipindahkan ke Sumedang.\n";
            } else cout << "Tidak ada paket di Bandung.\n";
        }
        else if (pilihan == 4) {
            string resi;
            cout << "Masukkan Nomor Resi: "; cin >> resi;
            bool ketemu = false;
            for (auto p : daftarPaket) {
                if (p->resi == resi) {
                    lacakResi(p);
                    ketemu = true;
                    break;
                }
            }
            if (!ketemu) cout << "Resi tidak ditemukan.\n";
        }
    } while (pilihan != 0);

    cout << "Program selesai.\n";
    return 0;
}
