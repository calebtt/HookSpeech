using System.Runtime.InteropServices;

namespace HookSpeechSharp
{
    internal static class HookProcDllImports
    {
        private const string DllName = "HookProcDLL.dll";

        [DllImport(DllName, CharSet = CharSet.Unicode, ExactSpelling = true, BestFitMapping = false, ThrowOnUnmappableChar = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern bool SetTranslationAlphabet([MarshalAs(UnmanagedType.LPWStr)] string s);
        [DllImport(DllName, CharSet = CharSet.Unicode, ExactSpelling = true, BestFitMapping = false, ThrowOnUnmappableChar = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr GetTranslationAlphabet();
        [DllImport(DllName, CharSet = CharSet.Ansi, ExactSpelling = true, BestFitMapping = false, ThrowOnUnmappableChar = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern bool SetWorkingAlphabet([MarshalAs(UnmanagedType.LPUTF8Str)] string s);
        [DllImport(DllName, CharSet = CharSet.Ansi, ExactSpelling = true, BestFitMapping = false, ThrowOnUnmappableChar = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr GetWorkingAlphabet();
        [DllImport(DllName)]
        public static extern bool AddHooks();
        [DllImport(DllName)]
        public static extern bool RemoveHooks();
        [DllImport(DllName)]
        public static extern bool IsHooked();
    }
}
