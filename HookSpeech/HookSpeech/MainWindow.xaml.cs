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

namespace HookSpeech
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        SetHooksClassLibrary.HooksWrapper h;

        public MainWindow()
        {
            InitializeComponent();
            h = new SetHooksClassLibrary.HooksWrapper();
            this.txbStatusText.Text = "Enabled.";
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            if (this.btnToggle.Content.ToString() == "Disable") 
            {
                try
                {
                    h.Toggle();
                    this.btnToggle.Content = "Enable";
                    this.txbStatusText.Text = "Disabled.";
                }
                catch(Exception ex)
                {
                    MessageBox.Show(ex.Message);
                }
            }
            else
            {
                try
                {
                    h.Toggle();
                    this.btnToggle.Content = "Disable";
                    this.txbStatusText.Text = "Enabled.";
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message);
                }
            }
        }

        private void btnUpdateAlphabet_Click(object sender, RoutedEventArgs e)
        {
            //Check text is 52 characters in length, if not display a message.
            if(this.tbxAlphabetText.Text.Length == 52)
            {
                if (!h.UpdateAlphabet(this.tbxAlphabetText.Text))
                {
                    //Display failure message.
                    MessageBox.Show("failed.");
                }
                else
                    this.txbStatusText.Text = "Alphabet updated.";
            }
            else
            {
                //Display error message about text length.
                this.txbStatusText.Text = "Error! New alphabet was incorrect length.";
                this.txbStatusText.Text += this.tbxAlphabetText.Text.Length.ToString() + "/52";
                //this.statusBar.Items.Add(new Label("Error. New alphabet was incorrect length."));
            }
        }
    }
}
