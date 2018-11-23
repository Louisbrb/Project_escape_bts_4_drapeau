using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace WpfApp1
{
    /// <summary>
    /// Logique d'interaction pour MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void valider_Click(object sender, RoutedEventArgs e)
        {
            if (champReponse.Text[champReponse.Text.Length - 1] == ' ')
            {
                champReponse.SelectionStart = 0;
                champReponse.SelectionLength = champReponse.Text.Length - 1;
                champReponse.Text = champReponse.SelectedText;
            }
            if (champReponse.Text == "réponse")
            {
                MessageBox.Show("Bravo! Vous avez résolu l'enigme.");
            }
            else if (champReponse.Text != "réponse")
            {
                MessageBox.Show("FAUX! Réessayez!");
                champReponse.Text = "";
            }
        }

        private void Indices_Click(object sender, RoutedEventArgs e)
        {
            MessageBox.Show("Insérez indice ici!\nInsérez indice ici\nInsérer indice ici");
        }

        private void mehdi_Click(object sender, RoutedEventArgs e)
        {
            MessageBox.Show("Il y a un correcteur d'ortographe.\nIl suffit d'appuyer sur \"ESPACE\" à la fin de votre réponse.\n\n-Mehdi （ゝ‿ ・）");
        }

        private void champReponse_GotFocus(object sender, RoutedEventArgs e)
        {
            if (champReponse.Text == "Entrez réponse")
            {
                champReponse.Text = "";
            }
            else if (champReponse.Text != "Entrez réponse")
            {
                champReponse.SelectionStart = 0;
                champReponse.SelectionLength = champReponse.Text.Length;
            }
        }

        private void champReponse_GotMouseCapture(object sender, MouseEventArgs e)
        {
            if (champReponse.Text == "Entrez réponse")
            {
                champReponse.Text = "";
            }
            else if (champReponse.Text != "Entrez réponse")
            {
                champReponse.SelectionStart = 0;
                champReponse.SelectionLength = champReponse.Text.Length;
            }
        }
    }
}
