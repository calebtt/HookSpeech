namespace HookSpeechSharp
{
    public partial class HssMainForm : Form
    {
        private const string MSG_TOGGLEHOOKS_DISABLE = "Disable";
        private const string MSG_TOGGLEHOOKS_ENABLE = "Enable";
        private const string MSG_BAD_TRANSLATION = "Can't update translation alphabet, most likely bad string length.";
        private const string MSG_BAD_ERROR = "Error";
        private readonly HookProcDllWrapper dllWrapper = new HookProcDllWrapper();
        public HssMainForm()
        {
            InitializeComponent();
            UpdateTranslationBox();
        }

        private void UpdateTranslationBox()
        {
            tbxAlphabetChars.Text = dllWrapper.GetTranslationAlphabet();
        }

        private void UpdateToggleHooksButton()
        {
            this.btnToggleEnabled.Text = dllWrapper.IsHooked() ? MSG_TOGGLEHOOKS_DISABLE : MSG_TOGGLEHOOKS_ENABLE;
        }

        private void btnToggleEnabled_Click(object sender, EventArgs e)
        {
            if (dllWrapper.IsHooked())
            {
                dllWrapper.RemoveHooks();
            }
            else
            {
                dllWrapper.AddHooks();
            }
            UpdateToggleHooksButton();
        }

        private void btnUpdateAlphabet_Click(object sender, EventArgs e)
        {
            if(!dllWrapper.SetTranslationAlphabet(tbxAlphabetChars.Text))
            {
                MessageBox.Show(MSG_BAD_TRANSLATION, MSG_BAD_ERROR, MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
            }
            UpdateTranslationBox();
        }
    }
}